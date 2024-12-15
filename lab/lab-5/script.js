let originalGraph = null;
let mstGraph = null;

function generateRandomGraph(nodeCount) {
    const nodes = Array.from({ length: nodeCount }, (_, i) => ({ data: { id: i.toString() } }));
    const edges = [];
    const maxWeight = 100;
    
    
    for (let i = 1; i < nodeCount; i++) {
        const weight = Math.floor(Math.random() * maxWeight) + 1;
        edges.push({
            data: {
                id: `${i-1}-${i}`,
                source: (i-1).toString(),
                target: i.toString(),
                weight: weight
            }
        });
    }
    
    
    const edgeCount = nodeCount * 2; 
    while (edges.length < edgeCount) {
        const u = Math.floor(Math.random() * nodeCount);
        const v = Math.floor(Math.random() * nodeCount);
        if (u !== v) {
            const weight = Math.floor(Math.random() * maxWeight) + 1;
            const edgeId = `${u}-${v}`;
            const reverseEdgeId = `${v}-${u}`;
            
            // 检查边是否已存在
            if (!edges.some(e => e.data.id === edgeId || e.data.id === reverseEdgeId)) {
                edges.push({
                    data: {
                        id: edgeId,
                        source: u.toString(),
                        target: v.toString(),
                        weight: weight
                    }
                });
            }
        }
    }
    
    return { nodes, edges };
}

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
            return true;
        }
        return false;
    }
}

function kruskal(nodes, edges) {
    const mstEdges = [];
    const dsu = new DSU(nodes.length);
    
    
    const sortedEdges = [...edges].sort((a, b) => a.data.weight - b.data.weight);
    
    for (const edge of sortedEdges) {
        const u = parseInt(edge.data.source);
        const v = parseInt(edge.data.target);
        
        if (dsu.unite(u, v)) {
            mstEdges.push(edge);
        }
    }
    
    return mstEdges;
}
const graphStyle = [
    {
        selector: 'node',
        style: {
            'background-color': '#666',
            'label': 'data(id)',
            'color': '#fff',
            'text-outline-color': '#666',
            'text-outline-width': 2,
            'font-size': '20px'
        }
    },
    {
        selector: 'edge',
        style: {
            'width': 3,
            'line-color': '#ccc',
            'target-arrow-color': '#ccc',
            'target-arrow-shape': 'triangle',
            'curve-style': 'bezier',
            'label': 'data(weight)',
            'font-size': '14px'
        }
    },
    {
        selector: '.mst',
        style: {
            'line-color': '#2ECC40',
            'target-arrow-color': '#2ECC40',
            'width': 5
        }
    }
];

function initializeGraphs(elements) {
    
    if (originalGraph) {
        originalGraph.destroy();
    }
    if (mstGraph) {
        mstGraph.destroy();
    }

    
    originalGraph = cytoscape({
        container: document.getElementById('original-graph'),
        elements: elements,
        style: graphStyle,
        layout: {
            name: 'circle',
            fit: true,
            padding: 30
        }
    });

    // 创建MST图
    const mstEdges = kruskal(elements.nodes, elements.edges);
    mstGraph = cytoscape({
        container: document.getElementById('mst-graph'),
        elements: {
            nodes: elements.nodes,
            edges: mstEdges
        },
        style: graphStyle,
        layout: {
            name: 'circle',
            fit: true,
            padding: 30
        }
    });

    
    mstGraph.edges().addClass('mst');
}

// 事件监听
document.getElementById('generate-graph').addEventListener('click', () => {
    const nodeCount = parseInt(document.getElementById('node-count').value);
    if (nodeCount < 2 || nodeCount > 100) {
        alert('节点数量必须在2到100之间');
        return;
    }
    
    const graphData = generateRandomGraph(nodeCount);
    initializeGraphs(graphData);
});