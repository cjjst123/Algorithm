// hdu 3460
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<set>
#include<queue>

#define ll long long
const int maxn = 100009;


using namespace std;
struct node{
	int next[128];
	int cnt, fail, idx;
}a[maxn];

int trie_ptr, rt;

int new_trie_node(){
	int idx = trie_ptr++;
	node &tmp = a[idx];
	for(int i=0; i<128; ++i)
		tmp.next[i] = -1;
	tmp.cnt = 0;
	tmp.fail = 0;

	return idx;
}

void trie_init(){
	trie_ptr = 0;
	rt = new_trie_node();
}

void trie_insert(char s[], int idx){
	int ptr = rt;

	for(int i = 0; s[i]; ++i){
		node &tmp = a[ptr];
		if( tmp.next[ s[i] - 0 ] == -1 )
			tmp.next[ s[i] - 0 ] = new_trie_node();
		ptr = tmp.next[ s[i] - 0 ];
	}
	++a[ptr].cnt;
	a[ptr].idx = idx;
}
 
void ac_auto(){
	queue<int> que;
	que.push(rt);
	while(!que.empty()){
		int ptr = que.front();
		que.pop();
		node &tmp = a[ptr];
		for(int i=0; i<128; ++i)
			if( tmp.next[i] != -1){
				int child = tmp.next[i];
				int pa = ptr;
				// For strings with length 1
				a[child].fail = 0;
				
				while( pa ){
					pa = a[pa].fail;
					if( a[pa].next[i]!= -1 ){
						a[child].fail = a[pa].next[i];
						break;
					}
				}	
				que.push(child);
			}
	}
}

set<int> query(char s[]){
	set<int> st;

	int ptr = rt;
	int i = 0;
	while(s[i]){
		if( a[ptr].next[ s[i] - 0 ] != -1 ){
			ptr = a[ptr].next[ s[i] - 0 ];

			if( a[ptr].cnt ){
				st.insert(a[ptr].idx);
				// uncertain
				// ptr = a[ptr].fail;
				ptr = rt;
			}
			++i;
		}
		else{
			if(ptr == 0)
				++i;
			else
				ptr = a[ptr].fail;
		}
	}
	// printf("\n");
	return st;
}

char virus[209],web[10009];

int main(){
	int n,m;
	trie_init();
	scanf("%d",&n);
	for(int i=1; i<=n; ++i){
		scanf("%s",virus);
		trie_insert(virus,i);
	}
	ac_auto();
	scanf("%d",&m);
	int total = 0;
	for(int i=1; i<=m; ++i){
		scanf("%s",web);
		set<int> st = query(web);
		if(st.size()){
			printf("web %d:",i);
			set<int>::iterator it;
			for(it = st.begin(); it!=st.end(); it++)
				printf(" %d",*it);
			printf("\n");
			++total;
		}
	}
	printf("total: %d\n",total);
}