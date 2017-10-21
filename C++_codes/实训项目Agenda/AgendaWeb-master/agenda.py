from flask import Flask, render_template, url_for, session, escape, redirect, request, flash, json, g
from flask_session import Session
from flask_sqlalchemy import SQLAlchemy
from datetime import timedelta  # used to set session lifetime
import torndb, re, os
from datetime import datetime
from datetime import timedelta
from AgendaService import AgendaService
from hashlib import md5
from configparser import *



def get_db():
    if not hasattr(g, 'mysql_db'):
        g.mysql_db = torndb.Connection(g.dbhost, g.dbname, g.dbuser, g.dbpasswd)
    return g.mysql_db

def generate_response(status, message):
    return json.dumps({
        'status': status,
        'message': message
    })

app = Flask(__name__)
app.config['SESSION_TYPE']='filesystem'
app.config['SECRET_KEY']=os.urandom(24)
db = SQLAlchemy(app)
Session(app)

@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'mysql_db'):
        g.mysql_db.close()

@app.errorhandler(404)
def not_found(error):
    flash("404 Not Found Occured just now", "error")
    return redirect(url_for('meetings'))

@app.errorhandler(500)
def internal_error(error):
    flash("500 Internal Error Occured just now", "error")
    return redirect(url_for('meetings'))

with app.app_context():
    conf = ConfigParser()
    conf.read('agenda.conf')
    app.config['SERVER_NAME'] = conf.get('Agenda', 'SERVER_NAME')
    app.config['SESSION_COOKIE_DOMAIN'] = conf.get('Agenda', 'SESSION_COOKIE_DOMAIN')
    app.secret_key = conf.get('Agenda', 'SECRET_KEY')

@app.before_first_request
def initialize():
    conf = ConfigParser()
    conf.read('agenda.conf')

@app.before_request
def make_session_permanent():
    g.dbhost = conf.get('Agenda', 'DB_HOST')
    g.dbname = conf.get('Agenda', 'DB_NAME')
    g.dbuser = conf.get('Agenda', 'DB_USER')
    g.dbpasswd = conf.get('Agenda', 'DB_PASSWORD')
    g.service = AgendaService(get_db())
    if not hasattr(g, 'service'):
        g.service = AgendaService(get_db())
    session.permanent = True
    app.permanent_session_lifetime = timedelta(minutes=10)

@app.route('/query_all_users', methods=['POST', 'GET'])
def query_all_users():
    if 'username' in session:
        try:
            ret = g.service.listAllUsers()
        except Exception as e:
            print(e)
            return generate_response('ER', 'Unexpected Error')
        return json.dumps(ret)
    return generate_response('ER', 'Not logged in')

@app.route('/query_meeting_member', methods=['POST', 'GET'])
def query_meeting_member():
    if 'username' in session:
        # If logged in
        if 'title' in request.form:
            # If postdata correct
            try:
                info = g.service.getMeetingInfo(request.form['title'])
                # info = test_info
                if info:
                    # Info is not None
                    ret = {
                        'sponsor': info['sponsor'],
                        'participators': info['participators'],
                        'status': "OK"
                    }
                    return json.dumps(ret)
                else:
                    # Info is None
                    return generate_response('ER', 'No this meeting')
            except Exception as e:
                print(e)
                return generate_response('ER', 'Unexpected Error')
        else:
            # postdata wrong
            return generate_response('ER', 'No title in form data')
    else:
        return generate_response('ER', 'Not logged in')


@app.route('/query_meeting_info', methods=['POST', 'GET'])
def query_meeting_info():
    if 'username' in session:
        if 'title' in request.form:
            info = g.service.getMeetingInfo(request.form['title'])
            # info = test_info
            if info:
                ret = info
                return json.dumps(ret)
            else:
                # Info is None
                return generate_response('ER', 'No this Meeting')
        else:
            return generate_response('ER', 'Not title in form data')
    else:
        return generate_response('ER', 'Not logged in')

@app.route('/dodeletemeeting', methods=['POST', 'GET'])
def dodeletemeeting():
    if 'username' in session:
        try:
            g.service.deleteMeeting(session['username'], [request.form['title']])
            flash("Delete meeting Succeeded.", "succ")
            return redirect(url_for('meetings'))
        except:
            flash("Unexpected Error Occured.", "error")
            return redirect(url_for('meetings'))
    flash("Delete meeting failed.", "error")
    return redirect(url_for('login'))

@app.route('/dologin', methods=['GET', 'POST'])
def dologin():
    if 'username' in session:
        return redirect(url_for('meetings'))
    if request.method == 'POST':
        try:
            m = md5()
            m.update(request.form['password'])
            psw = m.hexdigest()
            if g.service.logIn(username=request.form['username'], password=psw):
                session['username'] = request.form['username']
                return redirect(url_for('meetings'))
            else:
                flash("Error username or password", "error")
                return redirect(url_for('login'))
        except:
            flash("Unexpected error occurred.", "error")
            return redirect(url_for('login'))
    return redirect(url_for('login'))


@app.route('/doregister', methods=['GET', 'POST'])
def doregister():
    if 'username' in session:
        return redirect(url_for('meetings'))
    if request.method == 'POST':
        # service register
        try:
            m = md5()
            m.update(request.form['password'])
            psw = m.hexdigest()
            if g.service.userRegister(username=request.form['username'], password=psw, email=request.form['email'], phone=request.form['phone']):
              flash("Register succeed! Now you can log in.", "succ")
              return redirect(url_for('login'))
            else:
              flash("Register failed for some reason", "error")
              return redirect(url_for('login'))
        except:
            flash("Register failed for exception occurred", "error")
            return redirect(url_for('login'))
    return redirect(url_for('login'))

@app.route('/dologout', methods=['GET', 'POST'])
def dologout():
    if 'username' in session:
        session.pop('username', None)
        flash("Log out successfully", 'succ')
        return redirect(url_for('login'))
    return redirect(url_for('login'))

@app.route('/dodeleteuser', methods=['GET', 'POST'])
def dodeleteuser():
    if 'username' in session:
        try:
            gen = md5()
            gen.update(request.form['password'])
            psw = gen.hexdigest()
            if g.service.deleteUser(username=session['username'], password=psw):
                flash("Deleted succeed. Enjoy your new life without Agenda!", "succ")
                session.pop('username', None)
                return redirect(url_for('login'))
            else:
                flash("Unexpected Error", "error")
                return redirect(url_for('meetings'))
        except:
            flash("Unexpected Error Occured", "error")
            return redirect(url_for('meetings'))
    return redirect(url_for('login'))

@app.route('/docreatemeeting', methods=['GET', 'POST'])
def docreatemeeting():
    if 'username' in session:
        try:
            startDatetime = datetime.strptime(request.form['startDate'], "%Y-%m-%dT%H:%M")
            endDatetime = datetime.strptime(request.form['endDate'], "%Y-%m-%dT%H:%M")
            if g.service.createMeeting(sponsor=session['username'], startDate=startDatetime, endDate=endDatetime, participators=request.form.getlist('participators'), title=request.form['title']):
                flash("Create Meeting Succeeded", "succ")
                return redirect(url_for('meetings'))
            else:
                flash("Create Meeting Failed", "error")
                return redirect(url_for('meetings'))
        except:
            flash("Something out of expectation occurred", "error")
            return redirect(url_for('login'))
    flash("Please log in first", 'error')
    return redirect(url_for('login'))

@app.route('/doupdateuser', methods=['GET', 'POST'])
def doupdateuser():
    if 'username' in session:
        try:
            gen = md5()
            gen.update(request.form['oldPassword'])        
            opsw = gen.hexdigest()
            npsw = ""
            if request.form['newPassword'] != "":
                gen = md5()
                gen.update(request.form['newPassword'])
                npsw = gen.hexdigest()
            else:
                npsw = None
            if g.service.updateUser(session['username'], opsw, password=npsw, email=request.form['email'] if 'email' in request.form else None, phone=request.form['phone'] if 'phone' in request.form else None):
                flash("Upadate Succeeded.", "succ")
                if npsw != None:
                    session.pop('username', None)
                    flash("For your safety, you are redirected to log in page", "succ")
                    return redirect(url_for('login'))
                return redirect(url_for('profile'))
            else:
                flash("Upadate Failed.", "error")
                return redirect(url_for('profile'))
        except:
            flash("Unexpected Error Occured", "error")
            return redirect(url_for('profile'))
            # print 'error'
            # flash("Unexpected error occurred")
            # return redirect(url_for('profile'))
    else:
        flash("Please login first")
        return redirect(url_for('login'))
    return redirect(url_for('profile'))

@app.route('/')
def login():
    if 'username' in session:
        return redirect(url_for('meetings'))
    return render_template('login.html')


@app.route('/meetings')
def meetings():
    if 'username' in session:
        try:
            allMeetings = g.service.listAllMeetings(session['username'])
            sponsorMeetings = g.service.listAllSponsorMeetings(session['username'])
            invitedMeetings = g.service.listAllParticipateMeetings(session['username'])
            
            now_datetime = datetime.now()
            recentMeetings = g.service.queryMeeting(session['username'], startDate=now_datetime, endDate=now_datetime + timedelta(days=3))
            pastMeetings = g.service.queryMeeting(session['username'], startDate=datetime(1,1,1,0), endDate=now_datetime)

            return render_template('meetings.html', allMeetings=allMeetings, sponsorMeetings=sponsorMeetings, invitedMeetings=invitedMeetings, recentMeetings=recentMeetings, pastMeetings=pastMeetings)
        except:
            flash("Unexpected Error Occured", "error")
            return redirect(url_for(login))

    flash("Please log in first", 'error')
    return redirect(url_for('login'))


@app.route('/users')
def users():
    if 'username' in session:
        try:
            allUsers = g.service.listAllUsers()
            return render_template('users.html', allUsers=allUsers)
        except Exception as e:
            flash("Unexpected Error occurred.", "error")
            print(e)
    flash("Please log in first", 'error')
    return redirect(url_for('login'))


@app.route('/profile')
def profile():
    if 'username' in session:
        try:
            li = g.service.queryUser(username=session['username'])
            return render_template('profile.html', email=li[0]['email'], phone=li[0]['phone'])
        except Exception as e:
            flash("Unexpected Error Occured.", "error")
    flash("Please log in first", 'error')
    return redirect(url_for('login'))


@app.route('/about')
def about():
    return render_template('about.html')
