def solve():
    MOD = 998244353
    
    def is_fib_like(seq):
        """Check if sequence of length >= 3 is Fibonacci-like"""
        if len(seq) < 3:
            return True  # All sequences of length 2 are "interesting"
        for i in range(2, len(seq)):
            if seq[i] != seq[i-1] + seq[i-2]:
                return False
        return True
    
    def dfs(node, path, labels, visited, graph):
        """Count mysterious paths starting from current path"""
        count = 0
        
        # Current path forms a sequence
        seq = [labels[v] for v in path]
        
        # If path length >= 2 and interesting, count it
        if len(path) >= 2 and is_fib_like(seq):
            count += 1
        
        # Try extending the path
        if node in graph:
            for neighbor in graph[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    path.append(neighbor)
                    count += dfs(neighbor, path, labels, visited, graph)
                    path.pop()
                    visited.remove(neighbor)
        
        return count % MOD
    
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())
        labels = [0] + list(map(int, input().split()))  # 1-indexed
        
        graph = {}
        for _ in range(m):
            u, v = map(int, input().split())
            if u not in graph:
                graph[u] = []
            graph[u].append(v)
        
        total = 0
        
        # Try starting from each vertex
        for start in range(1, n + 1):
            visited = {start}
            path = [start]
            total += dfs(start, path, labels, visited, graph)
            total %= MOD
        
        print(total)

solve()
