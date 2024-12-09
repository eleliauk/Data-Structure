document.getElementById("run-algorithm").addEventListener("click", (e) => {
    e.preventDefault();
  
    // 获取输入数据
    const nodeCount = parseInt(document.getElementById("node-count").value);
    const edgesInput = document.getElementById("edges").value.trim().split("\n");
    const edges = edgesInput.map(line => {
      const [u, v, weight] = line.split(" ");
      return { u, v, weight: parseFloat(weight) };
    });
  
    // 初始化 Cytoscape 图形
    const cy = cytoscape({
      container: document.getElementById("graph-canvas"),
      elements: [
        ...Array.from({ length: nodeCount }, (_, i) => ({ data: { id: i.toString() } })),
        ...edges.map(edge => ({
          data: { id: `${edge.u}-${edge.v}`, source: edge.u, target: edge.v, weight: edge.weight }
        })),
      ],
      style: [
        { selector: "node", style: { label: "data(id)", "background-color": "#0074D9" } },
        { selector: "edge", style: { label: "data(weight)", "line-color": "#FF4136", "target-arrow-color": "#FF4136" } },
      ],
      layout: { name: "circle" },
    });
  
    // Kruskal's Algorithm
    const sortedEdges = edges.sort((a, b) => a.weight - b.weight);
    const resultEdges = [];
    const dsu = new DSU(nodeCount);
  
    sortedEdges.forEach(edge => {
      if (dsu.find(edge.u) !== dsu.find(edge.v)) {
        dsu.unite(edge.u, edge.v);
        resultEdges.push(edge);
      }
    });
  
    // 高亮最小生成树边
    resultEdges.forEach(edge => {
      const edgeId = `${edge.u}-${edge.v}`;
      const reverseEdgeId = `${edge.v}-${edge.u}`;
      if (cy.getElementById(edgeId).length) {
        cy.getElementById(edgeId).style("line-color", "#2ECC40");
      } else {
        cy.getElementById(reverseEdgeId).style("line-color", "#2ECC40");
      }
    });
  
    // 显示结果
    const totalWeight = resultEdges.reduce((sum, edge) => sum + edge.weight, 0);
    document.getElementById("result").textContent = `最小生成树的总权重: ${totalWeight}`;
  });
  
  // Disjoint Set Union for Kruskal's Algorithm
  class DSU {
    constructor(n) {
      this.parent = Array.from({ length: n }, (_, i) => i);
    }
  
    find(x) {
      if (this.parent[x] !== x) {
        this.parent[x] = this.find(this.parent[x]);
      }
      return this.parent[x];
    }
  
    unite(x, y) {
      const rootX = this.find(x);
      const rootY = this.find(y);
      if (rootX !== rootY) {
        this.parent[rootY] = rootX;
      }
    }
  }