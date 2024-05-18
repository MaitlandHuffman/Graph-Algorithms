#include <climits>
#include <algorithm>
#include <queue>
#include <sys/time.h>
#include "ECLgraph.h"

static void Dijkstra(const int src, const ECLgraph& g, int* const dist, int* const parent)
{
  // initialize dist and parent array
  for (int i = 0; i < g.nodes; i++)
  {
    dist[i] = INT_MAX;
    parent[i] = 0;
  }
  dist[src] = 0;

  // set up priority queue with just source node in it
  std::priority_queue< std::pair<int, int> > pq;
  pq.push(std::make_pair(0, src));
  while (pq.size() > 0) {
    // process closest vertex
    const int v = pq.top().second;
    pq.pop();
    const int dv = dist[v];
    // visit outgoing neighbors
    for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++) {
      const int n = g.nlist[i];
      const int d = dv + g.eweight[i];
      // check if new lower distance found
      if (d < dist[n]) {
        dist[n] = d;
        parent[n] = v;
        pq.push(std::make_pair(-d, n));
      }
    }
  }
}


static void BellmanFord(const int src, const ECLgraph& g, int* const dist,int* const parent)
{
  // Initialize distances and parents
  for (int i = 0; i < g.nodes; i++)
  {
    dist[i] = INT_MAX;
    parent[i] = -1;
  }
  
  //initialize source distance to 0
  dist[src] = 0;
  
  bool changed = true;
  
  for (int i = 0; i < g.nodes- 1 && changed; i++)
  {
    changed = false;
    for (int u = 0; u < g.nodes; u++)
    {
      if (dist[u] != INT_MAX)
      {
        for (int j = g.nindex[u]; j < g.nindex[u+1]; j++)
        {
          const int v = g.nlist[j];
          const int weight = g.eweight[j];
          
          // check if lower distance found
          if (dist[u] + weight < dist[v])
          {
            dist[v] = dist[u] + weight;
            parent[v] = u;
            changed = true;
          }
        }
      } 
    }
  }
}


static void MST_prim(const int src, const ECLgraph& g, int* const dist, int* const prev, int* const color)
{
  // initialize distances and colors
  for(int i = 0; i < g.nodes; i++)
  {
    dist[i] = INT_MAX;
    color[i] = 0;
  }
  
  // initalize source node
  
  dist[src] = 0;

  //create PQ
  std::priority_queue< std::pair<int, int> > pq;
  // insert source node
  pq.push(std::make_pair(0, src));
  
  while (pq.size() > 0) 
  {
    const int v = pq.top().second;
    pq.pop();

    if(color[v] != 1)
    {
      color[v] = 1;
    
      for (int i = g.nindex[v]; i < g.nindex[v + 1]; i++)
      {
        const int u = g.nlist[i];
        const int weight = g.eweight[i];
        if (color[u] == 0 && weight < dist[u])
        {
          dist[u] = weight;
          prev[u] = v;
          pq.push(std::make_pair(dist[u], u));
        }
      }
    }
  }
}


int main(int argc, char* argv[])
{
  
  printf("MST & SSSP (%s)\n", __FILE__);
  if (argc != 2) {fprintf(stderr, "USAGE: %s input_file_name\n", argv[0]); exit(-1);}

  // process command line
  ECLgraph g = readECLgraph(argv[1]);
  if (g.eweight == NULL) {fprintf(stderr, "ERROR: graph must have weights\n"); exit(-1);}
  printf("input: %s\n", argv[1]);
  printf("nodes: %d\n", g.nodes);
  printf("edges: %d\n", g.edges);
  const int source = 0;
  if ((source < 0) || (source >= g.nodes)) {fprintf(stderr, "ERROR: source_node_number must be between 0 and %d\n", g.nodes); exit(-1);}
  printf("source: %d\n", source);

  //MST Prim
  int* const distance = new int[g.nodes];
  int* const prev = new int[g.nodes];
  int* const color = new int[g.nodes];

  MST_prim(source,g, distance, prev, color);
  //comment this part when running with the large graphs
  for (int v = 1; v < g.nodes; v++) {
    printf("(%d ,  %d) and dist %d \n", v, prev[v],distance[v]);
  }

  
  timeval start, end;
  // SSSP
  int* const dist = new int[g.nodes];
  int* const parent = new int[g.nodes];
  gettimeofday(&start, NULL);
  BellmanFord(source, g, dist, parent);
  gettimeofday(&end, NULL);
  printf("BellmanFord runtime: %.6f s\n", end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0);
  int maxnode = 0;
  for (int v = 1; v < g.nodes; v++) {
    if (dist[maxnode] < dist[v]) maxnode = v;
  }
  printf("vertex %d has maximum distance %d\n", maxnode, dist[maxnode]);

  // compare yout solutions
  int* const verify = new int[g.nodes];
  gettimeofday(&start, NULL);
  Dijkstra(source, g, verify, parent);
  gettimeofday(&end, NULL);
  printf("Dijkstra runtime: %.6f s\n", end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0);
  for (int v = 0; v < g.nodes; v++) {
    if (dist[v] != verify[v]) {fprintf(stderr, "ERROR: verification failed for node %d: %d instead of %d\n", v, dist[v], verify[v]); exit(-1);}
  }
  printf("verification passed\n\n");
 
  // free memory
  delete [] verify;
  delete [] distance;
  delete [] dist;
  delete [] prev;
  delete [] color;
  freeECLgraph(g);
  return 0;
}