/* �ʿ��� ������� �߰� */
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //���Ḯ��Ʈ ����ü Node
	int key;
	struct Node* llink; //���ʳ�带 ����ų �ڱ���������ü ������ llink
	struct Node* rlink; //�����ʳ�带 ����ų �ڱ���������ü ������ rlink
} listNode; //��Ī listNode

/* �Լ� ����Ʈ */
int initialize(listNode** h);// ������, �����޸� �Ҵ�
int freeList(listNode* h);   // ���Ḯ��Ʈ ��� �����޸� ����
int insertFirst(listNode* h, int key); // ���Ḯ��Ʈ ó����ġ ����߰�
int insertLast(listNode* h, int key);  // ���Ḯ��Ʈ ������ ��ġ�� ����߰�
int insertNode(listNode* h, int key);  // ���Ḯ��Ʈ �� �Էµ� key���� ū �� �տ� ����߰�
int deleteNode(listNode* h, int key);  // �˻��� �����ִ� ��� ����
int deleteFirst(listNode* h); // ���Ḯ��Ʈ ù ��� ����
int deleteLast(listNode* h);  // ���Ḯ��Ʈ ������ ��� ����
void printList(listNode* h);  // ���Ḯ��Ʈ ���
int invertList(listNode* h);  // ���Ḯ��Ʈ �Ųٷ� ������

int main()
{
    printf("[----- [����] [2019038029] -----]\n");
	char command; //��� �Է¹��� command
	int key;      //����Ʈ�� ���� ���� key
	listNode* headnode=NULL; //listNode ����ü ������ headnode
	initialize(&headnode); //���α׷� �ǵ��� �°� ���������� ���� �̸� �ʱ�ȭ �ǽ�
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
		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			initialize(&headnode); //headnode��ü�� �ּҸ� ����
			// �Լ� ������ headnode�� ���� �����ϱ� ����
			// (headnode�� ����Ű�� ���� �޸� �����Ҵ��� ����)
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
	return 1; //���α׷� ����
}

// ����� �����޸��Ҵ�
int initialize(listNode** h) { // headnode��ü�� �ּҰ� �޾ƿ�, �Լ����� *h=headnode �̴�
	// ���������ʹ� �����ͺ����� �ּҰ��� ���� ������
	if(*h != NULL) // head��忡 ����ִ� ���� ������ �󸮽�Ʈ�� �ƴϹǷ� 
		freeList(*h); // �Լ�ȣ���� �Ҵ�� �޸� ����
	*h = (listNode*)malloc(sizeof(listNode));
	// headnode�� ����Ű�� ������ listNode����ü ũ�� ��ŭ �����Ҵ� 
	(*h)->rlink = *h; //circular linked list �̹Ƿ�
	(*h)->llink = *h; //�������� rlink,llnik�� �ڱ��ڽ��� ����Ŵ
	(*h)->key = -9999; //Ű���� �ӽ÷� �־��
	return 1; //�Լ�����
}

//�����Ҵ� ����
int freeList(listNode* h){ 
	
	listNode* p = h->rlink; //������ ��� ����ü������ 1 - �̵��ϴ� ����,���� ù���� ���
	listNode* prev = NULL;  //������ ��� ����ü������ 2 - ������ġ ���� ����
	//���Ḯ��Ʈ ������ ���� �޸� ����
	while(p != h) { //p��ü�� ����� �϶����� �ݺ�
		prev = p;     //prev�� p�� ����
		p = p->rlink; //����Ű�� �������� �ٲ���
		free(prev);   //�����ص� prev��ġ �����޸� ����
	}
	free(h);  //����� �����޸� ����
	return 0; //�Լ�����
}

//����Ʈ ���
void printList(listNode* h) {
	int i = 0;   //�ε����� i 
	listNode* p; //����Ʈ�� �̵��ϸ� ��¿� �ҿ��� �뵵�� ����Ʈ ������ p
	printf("\n---PRINT\n");
	if(h == NULL) { //����Ʈ�� ����ִ� ���� ������
		printf("Nothing to print....\n");
		return; //�Լ�����
	}
	p = h->rlink; //��尡 ����Ű�� ����Ʈ ù��� �ּ� �־���
	while(p != NULL && p != h) {  //����Ʈ�� ������ �̵��� �������ΰ���Ű�� ���� ��尡 �ɶ����� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); 
		p = p->rlink; //���� ����Ʈ�� �̵� 
		i++; //������ �ݺ����� �ѹ� �����ǰ� �ݺ��� �����
	}
	printf("  items = %d\n", i); //����Ʈ�� ��� ���� ���

	//����Ʈ ������ �ּ� ���
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	i = 0; //�ε����� i�� �ٽ� 0���� �ʱ�ȭ
	p = h->rlink; //p�� �ٽ� ù��° ��� ����Ŵ
	while(p != NULL && p != h) { //����Ʈ�� ������ �̵��� �������ΰ���Ű�� ���� ��尡 �ɶ����� �ݺ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //���� ����Ʈ�� �̵� 
		i++;          //���� �ε����� �̵�
	}
}

//list �������� key�� ���� ��带 �߰�
int insertLast(listNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //�Է��� �� ��忡 �־���
	node->rlink=NULL; //�ϴ� ����� ��ũ����
	node->llink=NULL; //NULL�� �ʱ�ȭ �ص�
	//ù ��� ������ ��
	if (h->rlink==h){
		h->rlink=node; //����� rlink,llink ��� �����
		h->llink=node;
		node->rlink=h; //����� rlink,llink ��� �����
		node->llink=h;
		return 0; //�Լ�����
	}
	//�ƴ� �� => ���� ��ũ 2�� ����, node ��ũ 2�� ����
	node->rlink=h; //���rlink�� ��� ����Ŵ
	node->llink=h->llink; //���llink�� ��������Ʈ�� �������̿��� head�� llink ����Ŵ
	h->llink->rlink=node; //���� ����Ʈ�� ������ ��� �� rlink�� ��尡��Ŵ
	h->llink=node; // ��� llink�� ���� ���� ��� ����Ŵ
	return 0; //�Լ�����
}

//list�� ������ ��� ����
int deleteLast(listNode* h) {
	if (h->rlink == h) {     //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* rp = h->llink;  //������ ����ü ������,���� ����Ʈ�� ��������� ����Ŵ
	rp->llink->rlink=h; // ���ο� ������ ��尡 �� rp->llink�� rlink�� ���� ����
	h->llink=rp->llink; // ����� llink�� ���� ������ ��尡 �� rp->llink �� ����
	free(rp); // rp�� ����Ű�� ��ġ ���� �޸� ����
	return 0; //�Լ�����
}


//list ó���� key�� ���� ����ϳ��� �߰�
int insertFirst(listNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //�Է��� �� ��忡 �־���
	node->rlink=NULL; //�ϴ� ����� ��ũ����
	node->llink=NULL; //NULL�� �ʱ�ȭ �ص�

	//ù ��� �����ÿ��� �ᱹ h�� rlink,llink �� h �̹Ƿ� �Ʒ��� �ڵ�� ó���� �� ����
	node->rlink=h->rlink; //����� rlink�� ���� ����Ʈ�� ù��° ��忴�� ����� rlink
	node->llink=h; //����� llink�� ���
	h->rlink->llink=node; //���� ����Ʈ�� ù��° ����� llink�� ���θ��� ���
	h->rlink=node; //����� rlink�� ���θ��� ���
	return 1; //�Լ�����
}

//list�� ù��° ��� ����
int deleteFirst(listNode* h) {
	if (h->rlink == h) {     //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* rp = h->rlink;  //������ ����ü ������,���� ����Ʈ�� ù������� ����Ŵ
	rp->rlink->llink=h; // ����Ʈ�� ���ο� ù���� ��尡 �� rp->rlink�� llink�� ��� ����Ŵ
	h->rlink=rp->rlink; // ����� rlink�� ���� ù��° ����� ���� ��� 
	free(rp); //rp�� ����Ű�� ��ġ ���� �޸� ����
	return 0; //�Լ�����
}

//����Ʈ�� ��ũ�� �������� �� ��ġ
int invertList(listNode* h) {
	if (h->rlink == h) {     //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	//����ü ������ 3�� ����� ����Ʈ ������
	listNode *lead  = h->rlink; //���� �̵��ϴ� ����ü ������ 
	listNode *middle = h; //trail=middle �Ǹ鼭 ������ ����Ʈ�� �ᱹ ��带 ����Ŵ
	listNode *trail = NULL; 

	while(lead!=h){   //lead �����ü�� h �϶����� �ݺ� 
		trail=middle;     //trail �� middle �� �̵� ,ù�������� trail=h
		middle=lead;      //middle�� lead �� �̵�
		lead=lead->rlink; //lead�� �������� �̵��ϰ�
		middle->rlink=trail;  //middle�� rlink�� trail�� ����Ŵ,ù�������� middle�� h����Ű�Ե�
		middle->llink=lead;   //middle�� llink�� lead�� ����Ŵ
		//�������� lead�� h�� �Ǹ鼭 �ݺ��� ����
		//�ݺ��ϸ鼭 h->rlink,h->link�� �ǵ��� ����
	}
	//����� ����
	h->llink=h->rlink; //����� llink�� ���� ����Ű���ִ� ����� rlink 
	h->rlink=middle;   //����� rlink�� ������ ����Ʈ�� ù��°�� �� middle
	return 0; //�Լ����� 
}

//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(listNode* h, int key) {
	//�󸮽�Ʈ �϶�
	if (h->rlink == h){ 
		insertFirst(h, key); //����Ʈ ó����ġ ����߰��Լ� ȣ��
		return 0; //�Լ� ����
	}
	//���� �߰��� ��� ������ �����Ҵ�
	listNode * node =(listNode*)malloc(sizeof(listNode)); 
	node->key = key;  //�Է��� �� ��忡 �־���
	node->rlink=NULL; //�ϴ� ����� ��ũ����
	node->llink=NULL; //NULL�� �ʱ�ȭ �ص�

	//�߰��� ����� ���� �����ִ� ������ ������ �۰ų� ������
	listNode* searchN = h->rlink;  //�˻��� ����Ʈ ����ü ������
	//searchN�� �������� �Ѿ�鼭 searchN ������ ����϶����� �ݺ�
	while(searchN != h) {
		if( key <= (searchN->key) ) { // �ִ°��� �����ִ� ����Ʈ ������ ���� �� ��� ����
			if(searchN == h->rlink) { // ���� ����Ʈ ù��尪���� �ִ°��� ������ = h->rlink = node�� �Ǿ��� ��
				node->rlink=h->rlink; // ����� rlink�� ���� ����Ʈ�� ù��° ��忴�� ����� rlink
				node->llink=h; //����� llink�� ���
				h->rlink->llink=node; //���� ����Ʈ�� ù��° ����� llink�� ���θ��� ���
				h->rlink=node; //����� rlink�� ���θ��� ���
			} 
			else { //��������ġ�� �ƴ����� ���� ����Ʈ ������ �����ٴ� ���� ��� (���� ���̿� ����)
				node->rlink = searchN; //��� rlink�� ã�� ����� ������ ����
				node->llink = searchN->llink;  //��� llink�� ã�� ����� ������
				searchN->llink->rlink = node;  //ã�� ����� ����� �������� node���� 
				searchN->llink = node; // ã������� llink�� node�� ����
			}
			return 0; //�Լ�����
		}
		searchN = searchN->rlink; //searchN�� �������� �Ѿ
	}
	//�߰��� ����� ���� �����ִ� ��� ������ ������ Ŭ �� �������� �־���
	insertLast(h, key); //�������� ��� �ִ� �Լ� ȣ��
	return 0; //�Լ�����
}

//list���� key�� ���� ��� ����
int deleteNode(listNode* h, int key) {
	//�� ����Ʈ�� ������ ���� ���� ��	
	if (h->rlink == h) {     
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* rp = h->rlink;  //������ ����ü ������, ���� ����Ʈ�� ù������� ����Ŵ
	while(rp != h) { //�������� �Ѿ �����ü = ��� �϶����� �ݺ�-��������嵵 �˻��ؾߵǱ� ����
		if(rp->key == key) { //�Է��� Ű���� ã�� ����� Ű���� ���

			//����Ʈ�� ù��° ��带 ������ ���
			if(rp == h->rlink) { /* ù ���° ��� �ΰ�� */
				rp->rlink->llink=h; // ����Ʈ�� ���ο� ù���� ��尡 �� rp->rlink�� llink�� ��� ����Ŵ
				h->rlink=rp->rlink; // ����� rlink�� ���� ù��° ����� ���� ��� 
				free(rp); //rp�� ����Ű�� ��ġ ���� �޸� ����
			}
			// ����Ʈ ������ ��带 ������ ���
			else if (rp->rlink == h){ 
				rp->llink->rlink=h; // ���ο� ������ ��尡 �� rp->llink�� rlink�� ���� ����
				h->llink=rp->llink; // ����� llink�� ���� ������ ��尡 �� rp->llink �� ����
				free(rp); // rp�� ����Ű�� ��ġ ���� �޸� ����
			}
			//����Ʈ�� �߰���� ������ ���
			else { 
				rp->llink->rlink = rp->rlink; //ã�� ����� ���� ����� rlink�� ã����� �޳��� ����
				rp->rlink->llink = rp->llink; //ã�� ��� ���� llink�� ã����� �ճ��� ����
				free(rp); //rp�� ����Ű�� ��ġ ���� �޸� ����
			}
			return 0; //�Լ�����
		}
		rp = rp->rlink;// rp�� �������� �̵�
	}
	// ã�� key���� ���� ��尡 ������ 
	printf("Your key is not in the list\n"); //�ȳ��� ���
	return 0; //�Լ�����
}