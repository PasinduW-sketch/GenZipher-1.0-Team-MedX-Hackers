#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const long long MODULO = 1000000007;

struct Rectangle {
    long long x1, y1, x2, y2;
};

struct Event {
    long long x;
    long long y1, y2;
    int type; // 1 for start, -1 for end
    
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type > other.type; // process starts before ends
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<Rectangle> rects(n);
    vector<Event> events;
    vector<long long> yCoords;
    
    for (int i = 0; i < n; i++) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        
        events.push_back({rects[i].x1, rects[i].y1, rects[i].y2, 1});
        events.push_back({rects[i].x2, rects[i].y1, rects[i].y2, -1});
        
        yCoords.push_back(rects[i].y1);
        yCoords.push_back(rects[i].y2);
    }
    
    // Sort events by x coordinate
    sort(events.begin(), events.end());
    
    // Compress y coordinates
    sort(yCoords.begin(), yCoords.end());
    yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());
    
    map<long long, int> yIndex;
    for (int i = 0; i < yCoords.size(); i++) {
        yIndex[yCoords[i]] = i;
    }
    
    long long totalArea = 0;
    long long prevX = 0;
    vector<int> count(yCoords.size(), 0);
    
    for (const Event& e : events) {
        // Calculate the area contributed by the previous x position
        if (e.x != prevX) {
            long long height = 0;
            for (int i = 0; i < yCoords.size() - 1; i++) {
                if (count[i] > 0) {
                    height += yCoords[i + 1] - yCoords[i];
                }
            }
            
            long long width = e.x - prevX;
            long long area = (width % MODULO) * (height % MODULO) % MODULO;
            totalArea = (totalArea + area) % MODULO;
        }
        
        // Update the count array
        int idx1 = yIndex[e.y1];
        int idx2 = yIndex[e.y2];
        
        for (int i = idx1; i < idx2; i++) {
            count[i] += e.type;
        }
        
        prevX = e.x;
    }
    
    cout << totalArea << endl;
    
    return 0;
}
