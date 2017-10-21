#ifndef PRIM_HPP
#define PRIM_HPP

//Definitions of types
typedef float weight;
typedef int vertex;
typedef pair<vertex> edge;
typedef vector<edge> edges;
typedef map<vertex, bool> vertices;
typedef vector<vector<weight>> graphmatrix;
typedef vector<pair<vertex, weight>> labels;
float unlimit = numeric_limits<float> :: max();

//Prim Alogrithm
pair<edges, weight> prim(graphmatrix g, vertex s){
	int n = g.size();
	vertices V_T;
	for(int i=0;i<n;i++)
		V_T[i] = 0;
	V_T[s] = 1;
	edges E_T;
	weight w = 0;
	labels label(n);
	for(int i=0;i<n;i++)
		label[i] = make_pair(s, g[s][i]);
	for(int i=1;i<n;i++){
		int temp = nearest(V_T, label);
		V_T[temp] = 1;
		E_T.push_back(make_pair(temp, label[temp].first));
		w += g[temp][label[temp].first];
		for(int j=0;j<n;j++){
			if(!V_T[j]&&(g[temp][j]<unlimit)&&(g[temp][j]<label[j].second))
				label[j] = make_pair(temp, g[temp][j]);
		}
	}
	return make_pair(W_T, w);
}

vertex nearest(vertices V, labels label){
	vertex result;
	weight w = unlimit;
	int n = V.size();
	for(int i=0;i<n;i++){
		if(!V[i]&&label[i].second<w){
			w = label[i].second;
			result = i;
		}
	}
	return result;
}

#endif