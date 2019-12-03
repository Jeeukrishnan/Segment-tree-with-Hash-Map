#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
const int mx = 100005;//mx is the max size of segment tree
struct node {
	unordered_map<int, int> CountOccurrences;
	int Dominant;
} SegTree[4*mx];

int n, q, a[mx];
vector<int> QueryRanges;

void build(int x, int y, int r) {//Function to build the tree x-start of sub-segment tree,y- end of sub-segment tree
	if(x == y) {
		SegTree[r].CountOccurrences.clear();
		SegTree[r].CountOccurrences[a[x]] += 1;

		SegTree[r].Dominant = a[x];
		return;
	}

	int mid = (x+y)/2;
	build(x, mid, 2*r);
	build(mid+1, y, 2*r+1);

	int length = (y-x+1);
	SegTree[r].CountOccurrences.clear();

	unordered_map<int, int>::iterator it = SegTree[2*r].CountOccurrences.begin();//Modify the map of current node by map of left child
	while(it != SegTree[2*r].CountOccurrences.end()) {
		SegTree[r].CountOccurrences[it->first] += it->second;
		it++;
	}

	it = SegTree[2*r+1].CountOccurrences.begin(); //Modify the map of current node by map of right child
	while(it != SegTree[2*r+1].CountOccurrences.end()) {
		SegTree[r].CountOccurrences[it->first] += it->second;
		it++;
	}

	if(SegTree[r].CountOccurrences[SegTree[2*r].Dominant] > (length/2)) {
		   SegTree[r].Dominant = SegTree[2*r].Dominant;

	} else if (SegTree[r].CountOccurrences[SegTree[2*r+1].Dominant] > (length/2)) {
			SegTree[r].Dominant = SegTree[2*r+1].Dominant;

	} else {
		SegTree[r].Dominant = -1;
	}

	return;
}

void update(int x, int y, int r, int idx, int val, int oldVal) {//Update the node
	if(y < idx || x > idx) {
		return;
	}

	if(x == y) {//Leaf Node
		assert(x == idx);

		SegTree[r].CountOccurrences.clear();

		a[idx] = val;
		SegTree[r].CountOccurrences[a[idx]] += 1;
		SegTree[r].Dominant = a[idx];

		return;
	}

	int mid = (x+y)/2;
	update(x, mid, 2*r, idx, val, oldVal);
	update(mid+1, y, 2*r+1, idx, val, oldVal);

	int length = (y-x+1);

	SegTree[r].CountOccurrences[oldVal] -= 1;
	SegTree[r].CountOccurrences[val] += 1;

	if(SegTree[r].CountOccurrences[SegTree[2*r].Dominant] > (length/2)) {
		   SegTree[r].Dominant = SegTree[2*r].Dominant;

	} else if (SegTree[r].CountOccurrences[SegTree[2*r+1].Dominant] > (length/2)) {
			SegTree[r].Dominant = SegTree[2*r+1].Dominant;

	} else {
		SegTree[r].Dominant = -1;
	}

	return;
}

void query(int x, int y, int r, int qs, int qe) {//Perform query operation
	if(y < qs || qe < x) {//No overlap
		return;
	}

	if(qs <=x && y<=qe) {//Complete overlap
		QueryRanges.push_back(r);
		return;
	}
    //Partial Overlap
	int mid = (x+y)/2;
	query(x, mid, 2*r, qs, qe);
	query(mid+1, y, 2*r+1, qs, qe);
}


int main()
{

//       _    ______     ___    _   _  ____ _____ ____    ____  _____ ____ __  __ _____ _   _ _____   _____ ____  _____ _____
 cout<<"     / \\  |  _ \\ \\   / / \\  | \\ | |/ ___| ____|  _ \\  / ___|| ____/ ___|  \\/  | ____| \\ | |_   _| |_   _|  _ \\| ____| ____|"<<endl;
 cout<<"    / _ \\ | | | \\ \\ / / _ \\ |  \\| | |   |  _| | | | | \\___ \\|  _|| |  _| |\\/| |  _| |  \\| | | |     | | | |_) |  _| |  _| "<<endl;
 cout<<"   / ___ \\| |_| |\\ V / ___ \\| |\\  | |___| |___| |_| |  ___) | |__| |_| | |  | | |___| |\\  | | |     | | |  _ <| |___| |___ "<<endl;
 cout<<"  /_/   \\_\\____/  \\_/_/   \\_\\_| \\_|\\____|_____|____/  |____/|_____\\____|_|  |_|_____|_| \\_| |_|     |_| |_| \\_\\_____|_____| "<<endl;

	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n\n";

//






    cout<<"Our idea is to use hash table in Segment tree\n";
    cout<<"User will enter an array and can give two types of queries-\n1.Update any element in the array\n2.User will give a subarray and program will return the dominant term(The number that appears more than half of length of subarray)in the subarray\n";

	cout<<"-------------------------------------------------------------------------------------------------------------------------------\n\n";
	cout<<"Enter number of elements of array-";
	cin >> n;
	cout<<"Enter the array elements\n";
	for(int i=1;i<=n;i++) {
		cin >> a[i];
	}


	build(1, n, 1);

	do{
		cout<<"Enter your choice \n1.Update index with its new value\n2.Find dominant term in the range\n";
		int type;
		cin >> type;

		switch (type) {
		case 1:
			cout<<"Enter the index and its new value\n";
			int idx, val;
			cin >> idx >> val;
			update(1, n, 1, idx, val, a[idx]);
            cout<<"New Array\n";
            for(int i=1;i<=n;i++)
                cout<<a[i]<<" ";
            cout<<endl;

			break;

		case 2:
			cout<<"Enter left index and right index of the subarray for which you want to find dominant term\n";
			int qs, qe, length, found;
			cout<<"Left Index->";
			cin >> qs ;
			cout<<"Right index->";
			cin>> qe;
			cout<<endl;


			length = qe - qs + 1;
			found = 0;

			QueryRanges.clear();
			query(1, n, 1, qs, qe);

			for(int i=0;i<=QueryRanges.size()-1;i++) {
				int Count = 0;
				for(int j=0;j<=QueryRanges.size()-1;j++) {
					Count +=
						SegTree[QueryRanges[j]].CountOccurrences[SegTree[QueryRanges[i]].Dominant];
				}

				if(Count > length/2) {
					cout <<"The Dominant term is->"<<SegTree[QueryRanges[i]].Dominant<<"\n\n\n";
					found = 1;
					break;
				}
			}

			if (!found) {
				cout << "Sorry,There is no dominant number in the array\n\n\n";
			}

			break;
		}
		cout<<"DO YOU WANT TO ENTER MORE---";
		cin>>q;
	}while(q==1);

	return 0;

}
