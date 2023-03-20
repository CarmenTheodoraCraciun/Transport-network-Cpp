class Edge {
    string c1, c2;
    double d;
public:
    Edge(string c1, string c2, string d) {
        this->c1 = c1;
        this->c2 = c2;
        this->d = (stof)(d);
    }
    string getC1() { return this->c1; }
    string getC2() { return this->c2; }
    double getD() { return this->d; }
    friend ostream& operator<<(ostream& o, Edge e) {
        return o << e.c1 << " - " << e.c2;
    }
};