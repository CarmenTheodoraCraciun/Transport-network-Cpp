#ifndef LINKEDLISTELEM_H_
#define LINKEDLISTELEM_H_

#include <string>
#include <map>
using namespace std;

struct LinkedListElem;
using ElPtr = LinkedListElem*;

/** tail[x] refers to the last element in the linked list representation
 * of the set with representative x
 */
static map<ElPtr,ElPtr> tail;

/** len[x] refers to the size of the set with representative x
 */
static map<ElPtr,int> len;

/**
 * elem[s] refers to the element with string identifier s
 */
static map<string,ElPtr> LLelem;



struct LinkedListElem {

	string id;  		   // element name
	ElPtr next;  		   // pointer to next element in its set
	ElPtr representative;  // pointer to its representative

	LinkedListElem(string s) : id(s), next(0) {
		representative = this;
		tail[this] = this;
		len[this] = 1;
	}

	friend ostream& operator<<(ostream& o, LinkedListElem l) {
		return o << l.id;
	}

	string toString() { return id; }

	static ElPtr MakeSet(string s) {
		return new LinkedListElem(s);
	}

	static ElPtr FindSet(ElPtr x) { return x->representative; }

	static void Union(ElPtr x, ElPtr y,bool &unionDone) {
		ElPtr xSet = FindSet(x);
		ElPtr ySet = FindSet(y);
		if (xSet != ySet) {
			//cout << *x << " " << *y << endl;
			unionDone = true;
			if (len[xSet] < len[ySet]) { // swap xSet with ySet
				ElPtr tmp = xSet;
				xSet = ySet;
				ySet = tmp;
			}
			// find z = the last element of set xSet
			ElPtr z = tail[xSet];
			z->next = ySet;
			// remove ySet as a set representative from tail
			tail[xSet] = tail[ySet];
			len[xSet] += len[ySet];
			tail.erase(ySet);
			len.erase(ySet);
			z = ySet;
			while (z != 0) {
				z->representative = xSet;
				z = z->next;
			}
		}
	}
};

#endif /* LINKEDLISTELEM_H_ */
