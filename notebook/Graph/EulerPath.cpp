/*
 Undirected Graph
*/

void getTour(int u,vector<vector<int> > &edge,vector<PII> &edge_list,
 vector<int> &cyc){
   while(edge[u].size()){
      int k=edge[u][edge[u].size()-1];
      edge[u].pop_back();
      if(edge_list[k].first==-1)continue;
      int v=(edge_list[k].first==u)?edge_list[k].second:edge_list[k].first;
      edge_list[k].first=edge_list[k].second=-1;
      getTour(v,edge,edge_list,cyc);
      cyc.pb(u);
   }
}
vector<int> EulerTour(vector<vector<int> > &edge,vector<PII> edge_list){
   // Finding EulerTour in a undirected graph in O(E) 
   // Note that edge[u][i] is the index of an edge in edge_list
   // first vertex of 'cyc' is the same of the last vertex of 'cyc'
   vector<int> cyc;
   getTour(0,edge,edge_list,cyc);
   return cyc;
}

/*
 Directed Graph
*/
void go(int u,vector<vector<int> > &adj,vector<int> &rv){
  while(adj[u].size()!=0){
    int v=adj[u].back();
    adj[u].pop_back();
    go(v,adj,rv);
  }
  rv.push_back(u);
}
vector<int> EulerPath(vector<vector<int> > adj,int config){
  // Finding Euler Path/Cycle in a directed graph in O(E)
  // config=0: returns an Euler Path or Cycle
  // config=1: returns an Euler Path
  // config=2: returns an Euler Cycle
  // Returns an empty vector if it's impossible
  int odd=0,startingVertex=-1,endingVertex=-1,total_edges=0;
  vector<int> inDeg(adj.size(),0),outDeg(adj.size(),0);
  vector<int> rv;
  vector<bool> vis(adj.size(),false);
  for(int u=0;u<adj.size();u++){
    total_edges+=adj[u].size();
    for(int i=0;i<adj[u].size();i++){
      int v=adj[u][i];
      inDeg[v]++;
      outDeg[u]++;
    }
  }
  for(int u=0;u<adj.size();u++){
    if(outDeg[u]-inDeg[u]==1){
      if(startingVertex!=-1)return rv;
      startingVertex=u;
    }
    else if(outDeg[u]-inDeg[u]==-11){
      if(endingVertex!=-1)return rv;
      endingVertex=u;
    }
    else if(abs(inDeg[u]-outDeg[u])>1){
      return rv;
    }
  }
  if((config==1&&(startingVertex==-1||endingVertex==-1))||
     (config==2&(startingVertex!=-1||endingVertex!=-1))){
    return rv;
  }
  if(startingVertex==-1)startingVertex=0;
  go(startingVertex,adj,rv);
  reverse(rv.begin(),rv.end());
  // Check if the path actually goes through all vertices (G is connected)
  for(int i=0;i<rv.size();i++){
    vis[rv[i]]=true;
  }
  for(int i=0;i<adj.size();i++){
    if(!vis[i]){
      rv.clear();
      break;
    }
  }
  return rv;
}

