
#include <bits/stdc++.h>
using namespace std;

static const double EARTH_R = 6371.0;
static const double PI      = acos(-1.0);
static const double INF     = 1e18;

enum class T { NONE, WALK, CAR, METRO, BIKOLPO, UTTARA };

string tName(T t) {
    switch(t) {
        case T::WALK:   return "Walk";
          case T::CAR:    return "Car";
          case T::METRO:  return "Metro";
        case T::BIKOLPO:return "Bikolpo Bus";
         case T::UTTARA: return "Uttara Bus";
        default:        return "None";
    }
}

double costPerKm(T t) {
    switch(t) {
        case T::CAR:    return 20.0;
         case T::METRO:  return 5.0;
        case T::BIKOLPO:return 7.0;
         case T::UTTARA: return 10.0;
        default:        return 0.0;   
    }
}

double speedKmH(T t) {
    switch(t) {
        case T::CAR:    return 20.0;
         case T::METRO:  return 15.0;
         case T::BIKOLPO:return 10.0;
        case T::UTTARA: return 12.0;
        case T::WALK:   return 2.0;
        default:        return 30.0;
    }
}


struct LL {
    double lat, lon;
    LL() : lat(0), lon(0) {}
    LL(double la, double lo) : lat(la), lon(lo) {}

    bool operator==(const LL& o) const {
        return fabs(lat-o.lat)<1e-8 && fabs(lon-o.lon)<1e-8;
    }
    bool operator<(const LL& o) const {
         if(fabs(lat-o.lat)>1e-9) return lat < o.lat;
        return lon < o.lon;
    }
    string str() const {
         ostringstream s;
        s << fixed << setprecision(6) << "(" << lon << ", " << lat << ")";
        return s.str();
    }
    string kml() const {
        ostringstream s;
         s << fixed << setprecision(6) << lon << "," << lat << ",0";
        return s.str();
    }
};

double toRad(double d) { return d * PI / 180.0; }

double hav(const LL& a, const LL& b) {
    double dLat = toRad(b.lat - a.lat);
     double dLon = toRad(b.lon - a.lon);
    double x = sin(dLat/2)*sin(dLat/2) +
                cos(toRad(a.lat))*cos(toRad(b.lat))*
               sin(dLon/2)*sin(dLon/2);
    return 2.0 * EARTH_R * asin(sqrt(x));
}

struct Schedule { int startMin, endMin, intervalMin; };

Schedule getSchedule(T t) {
    switch(t) {
        case T::BIKOLPO: return {7*60,  22*60, 20};
         case T::UTTARA:  return {6*60,  23*60, 10};
        case T::METRO:   return {1*60,  23*60, 5};
        default:         return {0, 24*60, 1};
    }
}

double waitTime(T t, double nowMin) {
    auto s = getSchedule(t);
    if(nowMin < s.startMin) return (double)(s.startMin - nowMin);
    if(nowMin >= s.endMin)  return -1.0;
    double rem = fmod(nowMin - s.startMin, (double)s.intervalMin);
    return (rem < 1e-9) ? 0.0 : (double)s.intervalMin - rem;
}

int parseTime(const string& s) {
    istringstream ss(s);
    int h, m; char c;
     ss >> h >> c >> m;
    string ap; ss >> ap;
    for(auto& ch : ap) ch = toupper(ch);
    if(ap == "PM" && h != 12) h += 12;
    if(ap == "AM" && h == 12) h = 0;
    return h*60 + m;
}

string minToTime(double mins) {
    int total = (int)round(mins);
     int h = (total/60) % 24, m = total % 60;
    string ap = h < 12 ? "AM" : "PM";
    int h12 = h % 12; if(!h12) h12 = 12;
    ostringstream s;
    s << h12 << ":" << setw(2) << setfill('0') << m << " " << ap;
    return s.str();
}

struct Node {
    LL pos;
    T  transport;
    string name;
    int id;
    Node(){}
    Node(LL p, T tr, string n="", int i=-1): pos(p), transport(tr), name(n), id(i){}
};

struct Edge {
    int to;
    double distKm;
    T transport;
};

struct Graph {
    vector<Node>          nodes;
    vector<vector<Edge>>  adj;
    map<pair<long long,long long>, int> pos2id;

    int getOrAdd(const LL& p, T tr, const string& nm="") {
        auto key = make_pair((long long)round(p.lon*1e6),
                             (long long)round(p.lat*1e6));
         auto it = pos2id.find(key);
        if(it != pos2id.end()) return it->second;
        int id = (int)nodes.size();
        nodes.push_back(Node(p, tr, nm, id));
        adj.push_back({});
        pos2id[key] = id;
        return id;
    }

    void addEdge(int u, int v, double d, T tr, bool bi=true) {
        adj[u].push_back({v, d, tr});
        if(bi) adj[v].push_back({u, d, tr});
    }

    int size() const { return (int)nodes.size(); }
};

string trim(const string& s) {
     size_t l = s.find_first_not_of(" \t\r\n");
    size_t r = s.find_last_not_of(" \t\r\n");
    return (l==string::npos) ? "" : s.substr(l, r-l+1);
}

vector<string> splitCSV(const string& line) {
    vector<string> fields;
    string cur; bool inQ = false;
    for(char c : line) {
        if(c=='"') inQ=!inQ;
         else if(c==',' && !inQ) { fields.push_back(trim(cur)); cur=""; }
        else cur += c;
    }
    fields.push_back(trim(cur));
    return fields;
}

LL parseLL(const string& a, const string& b) {
    double x = stod(trim(a)), y = stod(trim(b));
    return (x > y) ? LL(y, x) : LL(x, y);  
}

struct RoadSeg   { vector<LL> pts; double lenKm; };
struct TransRoute{ T type; vector<LL> stops; string startName, endName; };

vector<RoadSeg> parseRoadmap(const string& fname) {
    vector<RoadSeg> segs;
    ifstream f(fname);
    if(!f){ cerr<<"[WARN] Cannot open: "<<fname<<"\n"; return segs; }
    string line;
    while(getline(f, line)) {
         line = trim(line);
        if(line.empty()) continue;
         auto F = splitCSV(line);
         if(F.size() < 4) continue;
        double len = 0;
        try { len = stod(F.back()); } catch(...){ continue; }
        int nc = (int)F.size() - 3;       
        if(nc < 2 || nc%2 != 0) continue;
        RoadSeg seg; seg.lenKm = len;
        for(int i=1; i<=nc; i+=2)
            try { seg.pts.push_back(parseLL(F[i], F[i+1])); } catch(...){}
        if(seg.pts.size()>=2) segs.push_back(seg);
    }
    return segs;
}

vector<TransRoute> parseTransport(const string& fname, T type) {
    vector<TransRoute> routes;
    ifstream f(fname);
    if(!f){ cerr<<"[WARN] Cannot open: "<<fname<<"\n"; return routes; }
    string line;
    while(getline(f, line)) {
        line = trim(line);
        if(line.empty()) continue;
        auto F = splitCSV(line);
        if(F.size() < 5) continue;
        string startNm = trim(F[F.size()-2]);
        string endNm   = trim(F.back());
        int nc = (int)F.size() - 3;
        if(nc < 2 || nc%2 != 0) continue;
        TransRoute rt; rt.type=type; rt.startName=startNm; rt.endName=endNm;
        for(int i=1; i<=nc; i+=2)
            try { rt.stops.push_back(parseLL(F[i], F[i+1])); } catch(...){}
        if(rt.stops.size()>=2) routes.push_back(rt);
    }
    return routes;
}

struct GraphData {
    Graph g;
    vector<int> roadNodes, metroNodes, bikolpoNodes, uttaraNodes;

    struct SegRef { int u, v; double lenKm; vector<LL> pts; T tr; };
    vector<SegRef> segs;
};

GraphData buildGraph(const vector<RoadSeg>&    roads,
                     const vector<TransRoute>& metro,
                      const vector<TransRoute>& bikolpo,
                     const vector<TransRoute>& uttara,
                      bool useMetro=true,
                     bool useBikolpo=true,
                     bool useUttara=true)
{
    GraphData gd;
    Graph& g = gd.g;

    for(auto& seg : roads) {
        vector<int> ids;
        for(auto& p : seg.pts) {
            int id = g.getOrAdd(p, T::CAR);
            ids.push_back(id);
            gd.roadNodes.push_back(id);
        }
        double totalApprox = 0;
        for(int i=0;i+1<(int)seg.pts.size();i++)
            totalApprox += hav(seg.pts[i], seg.pts[i+1]);
        for(int i=0;i+1<(int)ids.size();i++) {
            double d = (totalApprox<1e-9)
                ? seg.lenKm / max(1,(int)ids.size()-1)
                : hav(seg.pts[i],seg.pts[i+1]) / totalApprox * seg.lenKm;
            g.addEdge(ids[i], ids[i+1], d, T::CAR);
            gd.segs.push_back({ids[i], ids[i+1], d, {seg.pts[i],seg.pts[i+1]}, T::CAR});
        }
    }
    sort(gd.roadNodes.begin(),gd.roadNodes.end());
    gd.roadNodes.erase(unique(gd.roadNodes.begin(),gd.roadNodes.end()),gd.roadNodes.end());

    auto addTr = [&](const vector<TransRoute>& routes, vector<int>& nodeList) {
        for(auto& rt : routes) {
            vector<int> ids;
            for(int i=0;i<(int)rt.stops.size();i++) {
                string nm = (i==0) ? rt.startName
                          : (i==(int)rt.stops.size()-1) ? rt.endName : "";
                int id = g.getOrAdd(rt.stops[i], rt.type, nm);
                ids.push_back(id);
                nodeList.push_back(id);
            }
            for(int i=0;i+1<(int)ids.size();i++) {
                double d = hav(rt.stops[i], rt.stops[i+1]);
                g.addEdge(ids[i], ids[i+1], d, rt.type);
                gd.segs.push_back({ids[i],ids[i+1],d,{rt.stops[i],rt.stops[i+1]},rt.type});
            }
        }
        sort(nodeList.begin(),nodeList.end());
        nodeList.erase(unique(nodeList.begin(),nodeList.end()),nodeList.end());
    };

    if(useMetro)   addTr(metro,   gd.metroNodes);
    if(useBikolpo) addTr(bikolpo, gd.bikolpoNodes);
    if(useUttara)  addTr(uttara,  gd.uttaraNodes);

    return gd;
}

LL closestOnSeg(const LL& p, const LL& a, const LL& b, double& t) {
    double ax=a.lon,ay=a.lat, bx=b.lon,by=b.lat, px=p.lon,py=p.lat;
    double dx=bx-ax, dy=by-ay, len2=dx*dx+dy*dy;
    if(len2<1e-18){t=0;return a;}
    t = max(0.0, min(1.0, ((px-ax)*dx+(py-ay)*dy)/len2));
    return LL(ay+t*dy, ax+t*dx);
}

int injectPoint(GraphData& gd, const LL& p, const string& label) {
    Graph& g = gd.g;

    auto key = make_pair((long long)round(p.lon*1e6),(long long)round(p.lat*1e6));
    if(g.pos2id.count(key)) return g.pos2id[key];

    double bestDist = INF; int bestSeg = -1; LL bestPt;
    for(int si=0;si<(int)gd.segs.size();si++) {
        auto& seg = gd.segs[si];
        for(int k=0;k+1<(int)seg.pts.size();k++) {
            double t; LL cl = closestOnSeg(p, seg.pts[k], seg.pts[k+1], t);
            double d = hav(p, cl);
            if(d < bestDist){ bestDist=d; bestSeg=si; bestPt=cl; }
        }
    }

    int newId = g.getOrAdd(p, T::WALK, label);

    if(bestSeg >= 0 && bestDist < 0.05) {
        auto& seg = gd.segs[bestSeg];
        int projId = g.getOrAdd(bestPt, seg.tr, "");
        double d1 = hav(g.nodes[seg.u].pos, bestPt);
        double d2 = hav(bestPt, g.nodes[seg.v].pos);
        g.addEdge(seg.u, projId, d1, seg.tr);
        g.addEdge(projId, seg.v, d2, seg.tr);
        g.addEdge(newId, projId, bestDist, T::WALK);
    } else {
        double best = INF; int bestNode = -1;
        auto check = [&](vector<int>& lst) {
            for(int id : lst) {
                double d = hav(p, g.nodes[id].pos);
                if(d < best){ best=d; bestNode=id; }
            }
        };
        check(gd.roadNodes);
        check(gd.metroNodes);
        check(gd.bikolpoNodes);
        check(gd.uttaraNodes);
        if(bestNode >= 0)
            g.addEdge(newId, bestNode, best, T::WALK);
    }
    return newId;
}

struct PathResult {
    bool   found = false;
    double totalCost  = INF;
    double totalDist  = 0;
    double totalTime  = 0;   
    vector<int>          nodeIds;
    vector<T>            transports;
    vector<double>       edgeDists;
    vector<double>       arrivalTimes; 
};

PathResult solveP1(GraphData& gd, int src, int dst) {
    int N = gd.g.size();
    vector<double> dist(N, INF);
    vector<int>    par(N, -1);
    vector<T>      parTr(N, T::NONE);
    vector<double> parD(N, 0);

    using State = pair<double,int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[src]=0; pq.push({0,src});

    while(!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if(d > dist[u]+1e-9) continue;
        for(auto& e : gd.g.adj[u]) {
            if(e.transport!=T::CAR && e.transport!=T::WALK) continue;
            double nd = dist[u]+e.distKm;
            if(nd < dist[e.to]-1e-9) {
                dist[e.to]=nd; par[e.to]=u; parTr[e.to]=e.transport; parD[e.to]=e.distKm;
                pq.push({nd,e.to});
            }
        }
    }

    PathResult res;
    if(dist[dst]>=INF) return res;
    res.found=true; res.totalCost=dist[dst]; res.totalDist=dist[dst];
    for(int c=dst;c!=-1;c=par[c]) {
        res.nodeIds.push_back(c);
        res.transports.push_back(parTr[c]);
        if(par[c]!=-1) res.edgeDists.push_back(parD[c]);
    }
    reverse(res.nodeIds.begin(),res.nodeIds.end());
    reverse(res.transports.begin(),res.transports.end());
    reverse(res.edgeDists.begin(),res.edgeDists.end());
    return res;
}
PathResult solveCheapest(GraphData& gd, int src, int dst, set<T> allowed) {
    int N = gd.g.size();
    vector<double> cost(N, INF);
    vector<int>    par(N, -1);
    vector<T>      parTr(N, T::NONE);
    vector<double> parD(N, 0);

    using State = pair<double,int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    cost[src]=0; pq.push({0,src});

    while(!pq.empty()) {
        auto [c,u] = pq.top(); pq.pop();
        if(c > cost[u]+1e-9) continue;
        for(auto& e : gd.g.adj[u]) {
            if(!allowed.count(e.transport)) continue;
            double nc = cost[u] + e.distKm * costPerKm(e.transport);
            if(nc < cost[e.to]-1e-9) {
                cost[e.to]=nc; par[e.to]=u; parTr[e.to]=e.transport; parD[e.to]=e.distKm;
                pq.push({nc,e.to});
            }
        }
    }

    PathResult res;
    if(cost[dst]>=INF) return res;
    res.found=true; res.totalCost=cost[dst];
    for(int c=dst;c!=-1;c=par[c]) {
        res.nodeIds.push_back(c);
        res.transports.push_back(parTr[c]);
        if(par[c]!=-1){ res.edgeDists.push_back(parD[c]); res.totalDist+=parD[c]; }
    }
    reverse(res.nodeIds.begin(),res.nodeIds.end());
    reverse(res.transports.begin(),res.transports.end());
    reverse(res.edgeDists.begin(),res.edgeDists.end());
    return res;
}

struct TConfig {
    double           startMin;     
    double           deadlineMin;   
    int              metric;       
    set<T>           allowed;
    map<T,double>    speeds;    
    bool             useSchedule;
};

struct TState {
    double score, timeMin;
    int    node;
    bool operator>(const TState& o) const { return score > o.score; }
};

PathResult solveTimed(GraphData& gd, int src, int dst, TConfig cfg) {
    int N = gd.g.size();
    vector<double> best(N, INF), bestTime(N, INF);
    vector<int>    par(N, -1);
    vector<T>      parTr(N, T::NONE);
    vector<double> parD(N, 0), parArr(N, -1), parWait(N, 0);

    auto spd = [&](T t) {
        return cfg.speeds.count(t) ? cfg.speeds.at(t) : speedKmH(t);
    };

    priority_queue<TState, vector<TState>, greater<TState>> pq;
    best[src]=0; bestTime[src]=cfg.startMin;
    pq.push({0, cfg.startMin, src});

    while(!pq.empty()) {
        auto [sc, tm, u] = pq.top(); pq.pop();
        if(sc > best[u]+1e-9) continue;

        for(auto& e : gd.g.adj[u]) {
            if(!cfg.allowed.count(e.transport)) continue;
            double s = spd(e.transport);
            if(s < 1e-9) continue;

            double wait = 0;
            if(cfg.useSchedule &&
               (e.transport==T::METRO || e.transport==T::BIKOLPO || e.transport==T::UTTARA)) {
                double w = waitTime(e.transport, tm);
                if(w < 0) continue;  
                wait = w;
            }

            double travel  = (e.distKm / s) * 60.0;
            double arrive  = tm + wait + travel;

            if(cfg.deadlineMin >= 0 && arrive > cfg.deadlineMin+1e-6) continue;

            double add = (cfg.metric==0)
                ? e.distKm * costPerKm(e.transport)
                : (wait + travel);

            double ns = best[u] + add;

            if(ns < best[e.to]-1e-9 ||
              (fabs(ns-best[e.to])<1e-9 && arrive < bestTime[e.to])) {
                best[e.to]=ns; bestTime[e.to]=arrive;
                par[e.to]=u; parTr[e.to]=e.transport;
                parD[e.to]=e.distKm; parArr[e.to]=arrive; parWait[e.to]=wait;
                pq.push({ns, arrive, e.to});
            }
        }
    }

    PathResult res;
    if(best[dst]>=INF) return res;
    res.found=true;
    if(cfg.metric==0) res.totalCost=best[dst];
    else              res.totalTime=best[dst];

    for(int c=dst;c!=-1;c=par[c]) {
        res.nodeIds.push_back(c);
        res.transports.push_back(parTr[c]);
        if(par[c]!=-1){
            res.edgeDists.push_back(parD[c]);
            res.arrivalTimes.push_back(parArr[c]);
            res.totalDist += parD[c];
        }
    }
    reverse(res.nodeIds.begin(),res.nodeIds.end());
     reverse(res.transports.begin(),res.transports.end());
    reverse(res.edgeDists.begin(),res.edgeDists.end());
     reverse(res.arrivalTimes.begin(),res.arrivalTimes.end());
    res.arrivalTimes.insert(res.arrivalTimes.begin(), cfg.startMin);
    return res;
}

struct Step {
    T      transport;
    double distKm, cost;
    double startTime, endTime;   
    string fromName, toName;
    vector<LL> path;
};

vector<Step> buildSteps(const GraphData& gd,
                        const PathResult& res,
                        double startMin = -1,
                        map<T,double> speeds = {})
{
    if(!res.found || res.nodeIds.size()<2) return {};

    auto spd = [&](T t) {
        return speeds.count(t) ? speeds.at(t) : speedKmH(t);
    };

    vector<Step> steps;
    int n=(int)res.nodeIds.size(), ei=0, i=1;

    while(i < n) {
        T tr = res.transports[i];
        Step s;
         s.transport = tr;
         s.distKm    = 0;
      s.fromName  = gd.g.nodes[res.nodeIds[i-1]].name;
      s.path.push_back(gd.g.nodes[res.nodeIds[i-1]].pos);

        while(i<n && res.transports[i]==tr) {
            s.distKm += (ei<(int)res.edgeDists.size()) ? res.edgeDists[ei] : 0;
            s.path.push_back(gd.g.nodes[res.nodeIds[i]].pos);
            ei++; i++;
        }
        s.toName = gd.g.nodes[res.nodeIds[i-1]].name;
        s.cost   = s.distKm * costPerKm(tr);
        s.startTime = s.endTime = -1;
        steps.push_back(s);
    }

    if(startMin >= 0) {
        double clock = startMin;
        for(auto& s : steps) {
            double wait = 0;
            if(s.transport==T::METRO || s.transport==T::BIKOLPO || s.transport==T::UTTARA) {
                double w = waitTime(s.transport, clock);
                if(w > 0) wait = w;
            }
            clock += wait;
            s.startTime = clock;
            double v = spd(s.transport);
            clock += (v>1e-9) ? (s.distKm/v*60.0) : 0;
            s.endTime = clock;
        }
    }
    return steps;
}

string posStr(const LL& p) {
    ostringstream s;
    s << fixed << setprecision(6) << "(" << p.lon << "," << p.lat << ")";
    return s.str();
}

void printOutput(int pno, const LL& src, const LL& dst,
                 const vector<Step>& steps,
                 double startMin=-1, double deadlineMin=-1)
{
    cout << "Problem No   : " << pno << "\n";
    cout << "Source       : " << src.str() << "\n";
    cout << "Destination  : " << dst.str() << "\n";
    if(startMin   >= 0) cout << "Start time   : " << minToTime(startMin)   << "\n";
    if(deadlineMin>= 0) cout << "Must reach by: " << minToTime(deadlineMin)<< "\n";
    cout << string(62,'-') << "\n";

    if(steps.empty()) { cout << "  [No route found]\n"; return; }

    double totCost=0, totDist=0;
    for(auto& s : steps) {
        totCost += s.cost; totDist += s.distKm;
        string fn = s.fromName.empty() ? posStr(s.path.front())
                                       : s.fromName+" "+posStr(s.path.front());
        string tn = s.toName.empty()   ? posStr(s.path.back())
                                       : s.toName+" "+posStr(s.path.back());
        if(s.startTime >= 0)
            cout << minToTime(s.startTime) << " - " << minToTime(s.endTime)
                 << ", Cost: Tk " << fixed << setprecision(2) << s.cost << ": ";
        else
            cout << "Cost: Tk " << fixed << setprecision(2) << s.cost
                 << " (" << setprecision(3) << s.distKm << " km): ";
        cout << tName(s.transport) << " from " << fn << " to " << tn << ".\n";
    }
    cout << string(62,'-') << "\n";
    cout << "Total distance : " << fixed << setprecision(3) << totDist << " km\n";
    cout << "Total cost     : Tk " << fixed << setprecision(2) << totCost << "\n";
    if(startMin>=0 && !steps.empty())
        cout << "Arrival time   : " << minToTime(steps.back().endTime) << "\n";
}

void writeKML(const string& fname, int pno,
              const LL& src, const LL& dst,
              const vector<Step>& steps)
{
    ofstream f(fname);
    if(!f){ cerr<<"[ERROR] Cannot write "<<fname<<"\n"; return; }

    auto col = [](T t) -> string {
        switch(t) {
            case T::CAR:    return "ffff0000";  
            case T::METRO:  return "ff00cc00";  
             case T::BIKOLPO:return "ff0000ff";  
             case T::UTTARA: return "ff00ccff";  
             case T::WALK:   return "ff888888";  
            default:        return "ffffffff";
        }
    };

    f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n<Document>\n"
      << "  <name>Problem " << pno << " Route</name>\n";

    set<T> seen; for(auto& s : steps) seen.insert(s.transport);
    for(T t : seen)
        f << "  <Style id=\"s"<<(int)t<<"\">\n"
          << "    <LineStyle><color>"<<col(t)<<"</color><width>4</width></LineStyle>\n"
          << "  </Style>\n";

    auto marker = [&](const string& nm, const LL& p){
        f << "  <Placemark><name>"<<nm<<"</name>"
          << "<Point><coordinates>"<<p.kml()<<"</coordinates></Point></Placemark>\n";
    };
    marker("Source", src);
    marker("Destination", dst);

    for(int si=0;si<(int)steps.size();si++) {
        auto& s = steps[si];
        f << "  <Placemark>\n"
          << "    <name>"<<tName(s.transport)<<" (step "<<si+1<<")</name>\n"
          << "    <styleUrl>#s"<<(int)s.transport<<"</styleUrl>\n"
          << "    <LineString><tessellate>1</tessellate><coordinates>\n";
        for(auto& p : s.path) f << "      " << p.kml() << "\n";
        f << "    </coordinates></LineString>\n  </Placemark>\n";
    }
    f << "</Document>\n</kml>\n";
    cout << "[KML] Saved: " << fname << "\n";
}

int main(int argc, char* argv[]) {
    if(argc < 6) {
        cout << "Usage: " << argv[0]
             << " <problem> <src_lat> <src_lon> <dst_lat> <dst_lon>"
             << " [start_time] [deadline]\n\n"
             << "Problems:\n"
             << "  1  Shortest distance      (car only)\n"
             << "  2  Cheapest cost          (car + metro)\n"
             << "  3  Cheapest cost          (car + metro + Bikolpo Bus)\n"
             << "  4  Cheapest with schedule (car + metro + Bikolpo Bus, needs start_time)\n"
             << "  5  Fastest with schedule  (car + metro + Bikolpo Bus, needs start_time)\n"
             << "  6  Cheapest with deadline (all modes, needs start_time + deadline)\n\n"
             << "Example:\n"
             << "  " << argv[0] << " 1 23.8739 90.3988 23.7601 90.3892\n"
             << "  " << argv[0] << " 6 23.8739 90.3988 23.7601 90.3892 \"5:43 PM\" \"8:12 PM\"\n";
        return 1;
    }

    int    pno  = atoi(argv[1]);
    LL     src(atof(argv[2]), atof(argv[3]));
    LL     dst(atof(argv[4]), atof(argv[5]));
    string tsStr = (argc>6) ? argv[6] : "";
    string tdStr = (argc>7) ? argv[7] : "";
    double tsMin = tsStr.empty() ? -1 : (double)parseTime(tsStr);
    double tdMin = tdStr.empty() ? -1 : (double)parseTime(tdStr);

    auto roads   = parseRoadmap  ("Roadmap-Dhaka.csv");
    auto metro   = parseTransport("Routemap-DhakaMetroRail.csv", T::METRO);
    auto bikolpo = parseTransport("Routemap-BikolpoBus.csv",     T::BIKOLPO);
    auto uttara  = parseTransport("Routemap-UttaraBus.csv",      T::UTTARA);
    cout << "  Roads: "   << roads.size()   << " segments\n"
         << "  Metro: "   << metro.size()   << " routes\n"
         << "  Bikolpo: " << bikolpo.size() << " routes\n"
         << "  Uttara: "  << uttara.size()  << " routes\n";

    bool wantMetro   = pno>=2;
    bool wantBikolpo = pno>=3;
    bool wantUttara  = pno>=6;

    GraphData gd = buildGraph(roads, metro, bikolpo, uttara,
                              wantMetro, wantBikolpo, wantUttara);
    cout << "Graph: " << gd.g.size() << " nodes, " << gd.segs.size() << " segments\n";

    int srcId = injectPoint(gd, src, "Source");
    int dstId = injectPoint(gd, dst, "Destination");

    PathResult    res;
    vector<Step>  steps;
    string        kml = "route_p" + to_string(pno) + ".kml";

    switch(pno) {
    case 1: {
        res   = solveP1(gd, srcId, dstId);
        steps = buildSteps(gd, res);
        printOutput(1, src, dst, steps);
        break;
    }
    case 2: {
        res   = solveCheapest(gd, srcId, dstId,
                    {T::CAR, T::METRO, T::WALK});
        steps = buildSteps(gd, res);
        printOutput(2, src, dst, steps);
        break;
    }
    case 3: {
        res   = solveCheapest(gd, srcId, dstId,
                    {T::CAR, T::METRO, T::BIKOLPO, T::WALK});
        steps = buildSteps(gd, res);
        printOutput(3, src, dst, steps);
        break;
    }
    case 4: {
        if(tsMin<0){ cerr<<"[ERROR] Problem 4 needs start_time\n"; return 1; }
        TConfig cfg;
        cfg.startMin    = tsMin; cfg.deadlineMin = -1;
        cfg.metric      = 0;     cfg.useSchedule = true;
        cfg.allowed     = {T::CAR, T::METRO, T::BIKOLPO, T::WALK};
        cfg.speeds      = {{T::CAR,30},{T::METRO,30},{T::BIKOLPO,30},{T::WALK,2}};
        res   = solveTimed(gd, srcId, dstId, cfg);
        steps = buildSteps(gd, res, tsMin, cfg.speeds);
        printOutput(4, src, dst, steps, tsMin);
        break;
    }
    case 5: {
        if(tsMin<0){ cerr<<"[ERROR] Problem 5 needs start_time\n"; return 1; }
        TConfig cfg;
        cfg.startMin    = tsMin; cfg.deadlineMin = -1;
        cfg.metric      = 1;     cfg.useSchedule = true;   
        cfg.allowed     = {T::CAR, T::METRO, T::BIKOLPO, T::WALK};
        cfg.speeds      = {{T::CAR,10},{T::METRO,10},{T::BIKOLPO,10},{T::WALK,2}};
        res   = solveTimed(gd, srcId, dstId, cfg);
        steps = buildSteps(gd, res, tsMin, cfg.speeds);
        printOutput(5, src, dst, steps, tsMin);
        break;
    }
    case 6: {
        if(tsMin<0||tdMin<0){ cerr<<"[ERROR] Problem 6 needs start_time AND deadline\n"; return 1; }
        TConfig cfg;
        cfg.startMin    = tsMin; cfg.deadlineMin = tdMin;
        cfg.metric      = 0;     cfg.useSchedule = true; 
        cfg.allowed     = {T::CAR, T::METRO, T::BIKOLPO, T::UTTARA, T::WALK};
        cfg.speeds      = {{T::CAR,20},{T::METRO,15},{T::BIKOLPO,10},{T::UTTARA,12},{T::WALK,2}};
        res   = solveTimed(gd, srcId, dstId, cfg);
        if(!res.found){
            cout << "\n[RESULT] No feasible route before deadline "
                 << minToTime(tdMin) << "\n";
            return 0;
        }
        steps = buildSteps(gd, res, tsMin, cfg.speeds);
        printOutput(6, src, dst, steps, tsMin, tdMin);
        break;
    }
    default:
        cerr << "[ERROR] Unknown problem: " << pno << "\n";
        return 1;
    }

    writeKML(kml, pno, src, dst, steps);
    return 0;
}