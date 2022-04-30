/* 필요한 헤더파일 추가 */
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //연결리스트 구조체 Node
	int key;
	struct Node* llink; //왼쪽노드를 가리킬 자기참조구조체 포인터 llink
	struct Node* rlink; //오른쪽노드를 가리킬 자기참조구조체 포인터 rlink
} listNode; //별칭 listNode

/* 함수 리스트 */
int initialize(listNode** h);// 노드생성, 동적메모리 할당
int freeList(listNode* h);   // 연결리스트 노드 동적메모리 해제
int insertFirst(listNode* h, int key); // 연결리스트 처음위치 노드추가
int insertLast(listNode* h, int key);  // 연결리스트 마지막 위치에 노드추가
int insertNode(listNode* h, int key);  // 연결리스트 내 입력된 key보다 큰 값 앞에 노드추가
int deleteNode(listNode* h, int key);  // 검색한 값이있는 노드 삭제
int deleteFirst(listNode* h); // 연결리스트 첫 노드 삭제
int deleteLast(listNode* h);  // 연결리스트 마지막 노드 삭제
void printList(listNode* h);  // 연결리스트 출력
int invertList(listNode* h);  // 연결리스트 거꾸로 뒤집기

int main()
{
    printf("[----- [이찬] [2019038029] -----]\n");
	char command; //명령 입력받을 command
	int key;      //리스트에 넣을 내용 key
	listNode* headnode=NULL; //listNode 구조체 포인터 headnode
	initialize(&headnode); //프로그램 의도에 맞게 오류방지를 위해 미리 초기화 실시
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);
		switch(command) { //사용자의 입력에 따른 명령 실행
		case 'z': case 'Z':
			initialize(&headnode); //headnode자체의 주소를 보냄
			// 함수 내에서 headnode를 직접 조작하기 위해
			// (headnode가 가리키는 곳의 메모리 동적할당을 위해)
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1; //프로그램 종료
}

// 헤드노드 동적메모리할당
int initialize(listNode** h) { // headnode자체의 주소값 받아옴, 함수에서 *h=headnode 이다
	// 이중포인터는 포인터변수의 주소값을 갖는 포인터
	if(*h != NULL) // head노드에 들어있는 값이 있으면 빈리스트가 아니므로 
		freeList(*h); // 함수호출해 할당된 메모리 해제
	*h = (listNode*)malloc(sizeof(listNode));
	// headnode가 가리키는 공간에 listNode구조체 크기 만큼 동적할당 
	(*h)->rlink = *h; //circular linked list 이므로
	(*h)->llink = *h; //헤드노드드의 rlink,llnik는 자기자신을 가리킴
	(*h)->key = -9999; //키값은 임시로 넣어둠
	return 1; //함수종료
}

//동적할당 해제
int freeList(listNode* h){ 
	
	listNode* p = h->rlink; //해제용 노드 구조체포인터 1 - 이동하는 역할,현재 첫번쨰 노드
	listNode* prev = NULL;  //해제용 노드 구조체포인터 2 - 현재위치 해제 역할
	//연결리스트 노드들의 동적 메모리 해제
	while(p != h) { //p자체가 헤드노드 일때까지 반복
		prev = p;     //prev에 p값 저장
		p = p->rlink; //가리키는 다음노드로 바꿔줌
		free(prev);   //저장해둔 prev위치 동적메모리 해제
	}
	free(h);  //헤드노드 동적메모리 해제
	return 0; //함수종료
}

//리스트 출력
void printList(listNode* h) {
	int i = 0;   //인덱스용 i 
	listNode* p; //리스트를 이동하며 출력에 할용할 용도의 리스트 포인터 p
	printf("\n---PRINT\n");
	if(h == NULL) { //리스트에 들어있는 것이 없으면
		printf("Nothing to print....\n");
		return; //함수종료
	}
	p = h->rlink; //헤드가 가리키는 리스트 첫노드 주소 넣어줌
	while(p != NULL && p != h) {  //리스트가 끝까지 이동에 다음으로가리키는 것이 헤드가 될때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); 
		p = p->rlink; //다음 리스트로 이동 
		i++; //마지막 반복에서 한번 증가되고 반복문 종료됨
	}
	printf("  items = %d\n", i); //리스트의 노드 개수 출력

	//리스트 노드들의 주소 출력
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	i = 0; //인덱스용 i를 다시 0으로 초기화
	p = h->rlink; //p는 다시 첫번째 노드 가리킴
	while(p != NULL && p != h) { //리스트가 끝까지 이동에 다음으로가리키는 것이 헤드가 될때까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //다음 리스트로 이동 
		i++;          //다음 인덱스로 이동
	}
}

//list 마지막에 key에 대한 노드를 추가
int insertLast(listNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //입력한 값 노드에 넣어줌
	node->rlink=NULL; //일단 노드의 링크들을
	node->llink=NULL; //NULL로 초기화 해둠
	//첫 노드 생성일 떄
	if (h->rlink==h){
		h->rlink=node; //헤드의 rlink,llink 모두 노드임
		h->llink=node;
		node->rlink=h; //노드의 rlink,llink 모두 헤드임
		node->llink=h;
		return 0; //함수종료
	}
	//아닐 때 => 원래 링크 2개 수정, node 링크 2개 설정
	node->rlink=h; //노드rlink는 헤드 가리킴
	node->llink=h->llink; //노드llink는 원래리스트의 마지막이였던 head의 llink 가리킴
	h->llink->rlink=node; //원래 리스트의 마지막 노드 의 rlink는 노드가리킴
	h->llink=node; // 헤드 llink는 새로 만든 노드 가리킴
	return 0; //함수종료
}

//list의 마지막 노드 삭제
int deleteLast(listNode* h) {
	if (h->rlink == h) {     //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* rp = h->llink;  //삭제용 구조체 포인터,현재 리스트의 마지막노드 가리킴
	rp->llink->rlink=h; // 새로운 마지막 노드가 될 rp->llink의 rlink를 헤드로 연결
	h->llink=rp->llink; // 헤드의 llink는 새로 마지막 노드가 될 rp->llink 로 연결
	free(rp); // rp가 가리키는 위치 동적 메모리 해제
	return 0; //함수종료
}


//list 처음에 key에 대한 노드하나를 추가
int insertFirst(listNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //입력한 값 노드에 넣어줌
	node->rlink=NULL; //일단 노드의 링크들을
	node->llink=NULL; //NULL로 초기화 해둠

	//첫 노드 생성시에도 결국 h의 rlink,llink 가 h 이므로 아래의 코드로 처리할 수 있음
	node->rlink=h->rlink; //노드의 rlink는 원래 리스트의 첫번째 노드였던 헤드의 rlink
	node->llink=h; //노드의 llink는 헤드
	h->rlink->llink=node; //원래 리스트의 첫번째 노드의 llink는 새로만든 노드
	h->rlink=node; //헤드의 rlink는 새로만든 노드
	return 1; //함수종료
}

//list의 첫번째 노드 삭제
int deleteFirst(listNode* h) {
	if (h->rlink == h) {     //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* rp = h->rlink;  //삭제용 구조체 포인터,현재 리스트의 첫번쨰노드 가리킴
	rp->rlink->llink=h; // 리스트의 새로운 첫번쨰 노드가 될 rp->rlink의 llink는 헤드 가리킴
	h->rlink=rp->rlink; // 헤드의 rlink는 원래 첫번째 노드의 다음 노드 
	free(rp); //rp가 가리키는 위치 동적 메모리 해제
	return 0; //함수종료
}

//리스트의 링크를 역순으로 재 배치
int invertList(listNode* h) {
	if (h->rlink == h) {     //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	//구조체 포인터 3개 사용해 리스트 뒤집기
	listNode *lead  = h->rlink; //먼저 이동하는 구조체 포인터 
	listNode *middle = h; //trail=middle 되면서 뒤집힌 리스트도 결국 헤드를 가리킴
	listNode *trail = NULL; 

	while(lead!=h){   //lead 노드자체가 h 일때까지 반복 
		trail=middle;     //trail 이 middle 로 이동 ,첫루프에서 trail=h
		middle=lead;      //middle이 lead 로 이동
		lead=lead->rlink; //lead는 다음으로 이동하고
		middle->rlink=trail;  //middle의 rlink는 trail을 가리킴,첫루프에서 middle은 h가리키게됨
		middle->llink=lead;   //middle의 llink는 lead을 가리킴
		//마지막에 lead가 h가 되면서 반복문 종료
		//반복하면서 h->rlink,h->link는 건들지 않음
	}
	//헤드노드 설정
	h->llink=h->rlink; //헤드의 llink는 원래 가리키고있던 헤드의 rlink 
	h->rlink=middle;   //헤드의 rlink는 뒤집은 리스트의 첫번째가 된 middle
	return 0; //함수종료 
}

//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(listNode* h, int key) {
	//빈리스트 일때
	if (h->rlink == h){ 
		insertFirst(h, key); //리스트 처음위치 노드추가함수 호출
		return 0; //함수 종료
	}
	//내용 추가할 노드 생성후 동적할당
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //입력한 값 노드에 넣어줌
	node->rlink=NULL; //일단 노드의 링크들을
	node->llink=NULL; //NULL로 초기화 해둠

	//추가할 노드의 값이 원래있던 노드들의 값보다 작거나 같을때
	listNode* searchN = h->rlink;  //검색용 리스트 구조체 포인터
	//searchN가 다음으로 넘어가면서 searchN 자제가 헤드일때까지 반복
	while(searchN != h) {
		if( key <= (searchN->key) ) { // 넣는값이 원래있던 리스트 값보다 작을 때 노드 삽입
			if(searchN == h->rlink) { // 원래 리스트 첫노드값보다 넣는값이 작을때 = h->rlink = node가 되야할 때
				node->rlink=h->rlink; // 노드의 rlink는 원래 리스트의 첫번째 노드였던 헤드의 rlink
				node->llink=h; //노드의 llink는 헤드
				h->rlink->llink=node; //원래 리스트의 첫번째 노드의 llink는 새로만든 노드
				h->rlink=node; //헤드의 rlink는 새로만든 노드
			} 
			else { //헤드다음위치는 아니지만 원래 리스트 노드들의 값보다는 작을 경우 (노드들 사이에 삽입)
				node->rlink = searchN; //노드 rlink는 찾은 노드의 앞으로 연결
				node->llink = searchN->llink;  //노드 llink는 찾은 노드의 앞으로
				searchN->llink->rlink = node;  //찾은 노드의 전노드 다음으로 node연결 
				searchN->llink = node; // 찾은노드의 llink는 node로 연결
			}
			return 0; //함수종료
		}
		searchN = searchN->rlink; //searchN은 다음으로 넘어감
	}
	//추가할 노드의 값이 원래있던 모든 노드들의 값보다 클 때 마지막에 넣어줌
	insertLast(h, key); //마지막에 노드 넣는 함수 호출
	return 0; //함수종료
}

//list에서 key에 대한 노드 삭제
int deleteNode(listNode* h, int key) {
	//빈 리스트라 삭제할 것이 없을 시	
	if (h->rlink == h) {     
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* rp = h->rlink;  //삭제용 구조체 포인터, 현재 리스트의 첫번쨰노드 가리킴
	while(rp != h) { //다음으로 넘어간 노드자체 = 헤드 일때까지 반복-마지막노드도 검사해야되기 때문
		if(rp->key == key) { //입력한 키값이 찾은 노드의 키값인 경우

			//리스트의 첫번째 노드를 삭제할 경우
			if(rp == h->rlink) { /* 첫 노드째 노드 인경우 */
				rp->rlink->llink=h; // 리스트의 새로운 첫번쨰 노드가 될 rp->rlink의 llink는 헤드 가리킴
				h->rlink=rp->rlink; // 헤드의 rlink는 원래 첫번째 노드의 다음 노드 
				free(rp); //rp가 가리키는 위치 동적 메모리 해제
			}
			// 리스트 마지막 노드를 삭제할 경우
			else if (rp->rlink == h){ 
				rp->llink->rlink=h; // 새로운 마지막 노드가 될 rp->llink의 rlink를 헤드로 연결
				h->llink=rp->llink; // 헤드의 llink는 새로 마지막 노드가 될 rp->llink 로 연결
				free(rp); // rp가 가리키는 위치 동적 메모리 해제
			}
			//리스트의 중간노드 삭제할 경우
			else { 
				rp->llink->rlink = rp->rlink; //찾은 노드의 앞의 노드의 rlink를 찾은노드 뒷노드로 연결
				rp->rlink->llink = rp->llink; //찾은 노드 뒤의 llink를 찾은노드 앞노드로 연결
				free(rp); //rp가 가리키는 위치 동적 메모리 해제
			}
			return 0; //함수종료
		}
		rp = rp->rlink;// rp는 다음으로 이동
	}
	// 찾는 key값을 가진 노드가 없을때 
	printf("Your key is not in the list\n"); //안내문 출력
	return 0; //함수종료
}