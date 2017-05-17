#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct StructTree{ //Структура дерева
int Key; //Ключ, относительно которого происхдит сравнение
struct StructTree *Left; //Левое поддерево
struct StructTree *Right; //Правое поддерево
struct StructTree *Back; //Узел выше
} TypeTree;

int StringCmp(int *TempInt1,int *TempInt2,char filename[]);
void FreeTree(TypeTree *Tree);
TypeTree *AddTree(TypeTree *Tree,int Elem);
TypeTree* TreeSearch(TypeTree* Tree,int SearchNum,int TypeSearch,int flag);
void PrintTree(TypeTree *Tree,int level);
void SaveFile(TypeTree *Tree,FILE **openFile);
void LoadFile(TypeTree **Tree,FILE **openFile);
void Analysis(TypeTree *Tree,int flag);
int CommandCheck(int TempNum1,int TempNum2,int TempNum3,int TempNum4,int *TempInt1,int *TempInt2);
void BackPtr(TypeTree *Tree,TypeTree *ptr);

int main(void){
    TypeTree *Tree=0,*TempTree;
    FILE *openFile;
    int True=1,SwitchNum,TempNum1=0,TempNum2=0;
    char filename[255];
    while(True){ //Цикл для множественного введения комманд
        system("CLS");
        printf("Enter command: ");
        SwitchNum=StringCmp(&TempNum1,&TempNum2,filename); //Получаем нужную для обработки информацию из комманды
        fflush(stdin);
        switch (SwitchNum){
        case 1: //Создаем корень дерева
            if (Tree==NULL){
                Tree=AddTree(Tree,TempNum1);
                Tree->Back=NULL;
            }
            else printf("Root was made\n");
        break;
        case 2: //Осуществляем добавление левого потомка узла
            TempTree=TreeSearch(Tree,TempNum2,1,1);
            if (TempTree==NULL){
                printf("Parent is not found or parent is full\n");
                break;
            }
            TempTree->Left=AddTree(TempTree->Left,TempNum1);
            TempTree->Left->Back=TempTree;
        break;
        case 3: //Осуществляем добавление правого потомка узла
            TempTree=TreeSearch(Tree,TempNum2,2,1);
            if (TempTree==NULL){ //Невозможно добавить
                printf("Parent is not found or parent is full\n");
                break;
            }
            TempTree->Right=AddTree(TempTree->Right,TempNum1);
            TempTree->Right->Back=TempTree;
        break;
        case 4: //Осуществляем добавление брата узла
            TempTree=TreeSearch(Tree,TempNum2,3,1);
            if (TempTree==NULL){ //Невозможно добавить
                printf("Free sibling is not found\n");
                break;
            }
            if (TempTree->Back->Left==NULL){
                TempTree->Back->Left=AddTree(TempTree->Back->Left,TempNum1);
                TempTree->Back->Left->Back=TempTree->Back;
            }
            if (TempTree->Back->Right==NULL){
                TempTree->Back->Right=AddTree(TempTree->Back->Right,TempNum1);
                TempTree->Back->Right->Back=TempTree->Back;
            }
        break;
        case 5: //Изменение значения корня дерева
            if (Tree==NULL){ //Корень не создан
                printf("Root is not made\n");
                break;
            }
            Tree->Key=TempNum1;
        break;
        case 6: //Изменение левого потомка узла
            TempTree=TreeSearch(Tree,TempNum2,4,1);
            if (TempTree==NULL){ //Узла не существует
                printf("Parent or child are not found\n");
                break;
            }
            TempTree->Left->Key=TempNum1;
        break;
        case 7: //Изменение правого потомка узла
            TempTree=TreeSearch(Tree,TempNum2,5,1);
            if (TempTree==NULL){ //Узла не существует
                printf("Parent or child is not found\n");
                break;
            }
            TempTree->Right->Key=TempNum1;
        break;
        case 8: //Изменение брата узла
            TempTree=TreeSearch(Tree,TempNum2,6,1);
            if (TempTree==NULL){ //Брат не найден
                printf("Sibling is not found\n");
                break;
            }
            TempTree->Key=TempNum1;
        break;
        case 9: //Удаляем все дерево
            if (Tree==NULL){ //Дерево не было создано
                printf("Tree is empty\n");
                break;
            }
            FreeTree(Tree);
            Tree=NULL;
        break;
        case 10: //Удаляем левого потомка родителя
            TempTree=TreeSearch(Tree,TempNum2,4,1);
            if (TempTree==NULL){ //Потомок не найден
                printf("Node is not found\n");
                break;
            }
            TempTree=TempTree->Left;
            TempTree->Back->Left=NULL;
            FreeTree(TempTree);
        break;
        case 11: //Удаляем правого потомка родителя
            TempTree=TreeSearch(Tree,TempNum2,5,1);
            if (TempTree==NULL){ //Потомок не найден
                printf("Node is not found\n");
                break;
            }
            TempTree=TempTree->Right;
            TempTree->Back->Right=NULL;
            FreeTree(TempTree);
        break;
        case 12: //Удаляем брата узла
            TempTree=TreeSearch(Tree,TempNum2,6,1);
            if (TempTree==NULL){ //Брат не найден
                printf("Sibling is not found\n");
                break;
            }
            if (TempTree->Back->Left==TempTree)
                TempTree->Back->Left=NULL;
            if (TempTree->Back->Right==TempTree)
                TempTree->Back->Right=NULL;
            FreeTree(TempTree);
        break;
        case 13: //Выводим дерево
            PrintTree(Tree,0);
            break;
        case 14: //Сохраняем дерево
            openFile=fopen(filename,"w");
            SaveFile(Tree,&openFile);
            fclose(openFile);
            break;
        break;
        case 15: //Загружаем дерево
            FreeTree(Tree);
            openFile=fopen(filename,"r");
            if (openFile!=NULL){
                LoadFile(&Tree,&openFile);
                fclose(openFile);
                BackPtr(Tree,NULL); //Восстанавливаем указатели
            }else printf("Incorrect filename\n");
        break;
        case 16: //Помощь
            printf("1.add root KEY\n");
            printf("2.add node KEY left parent KEY\n");
            printf("3.add node KEY right parent KEY\n");
            printf("4.add node KEY sibling KEY\n");
            printf("5.renew root\n");
            printf("6.renew node KEY left parent KEY\n");
            printf("7.renew node KEY right parent KEY\n");
            printf("8.renew node KEY sibling KEY\n");
            printf("9.del tree\n");
            printf("10.del left parent KEY\n");
            printf("11.del right parent KEY\n");
            printf("12.del sibling KEY\n");
            printf("13.show\n");
            printf("14.save filename\n");
            printf("15.load filename\n");
            printf("16.help\n");
            printf("17.analysis\n");
            printf("18.exit\n");
            system("pause");
            system("CLS");
        break;
        case 17: //Анализ дерева
            Analysis(Tree,1);
        break;
        case 18: //Выходим из программы
            FreeTree(Tree);
            return 0;
        break;
        default: //Неправильная комманда
            printf("Incorrect command\n");
        }
        system("pause");
    }
}

//Функция по обработке комманд
int StringCmp(int *TempInt1,int *TempInt2,char filename[]){
    char Command[255];
    scanf("%s",Command);
    if (strcmp(Command,"help")==0)
        return 16;
    if (strcmp(Command,"show")==0)
        return 13;
    if (strcmp(Command,"exit")==0)
        return 18;
    if (strcmp(Command,"save")==0){
        scanf("%s",filename);
        return 14;
    }
    if (strcmp(Command,"load")==0){
        scanf("%s",filename);
        return 15;
    }
    if (strcmp(Command,"analysis")==0)
        return 17;
    if (strcmp(Command,"add")==0)
        return CommandCheck(1,2,3,4,TempInt1,TempInt2);
    if (strcmp(Command,"renew")==0)
        return CommandCheck(5,6,7,8,TempInt1,TempInt2);
    if (strcmp(Command,"del")==0){
        scanf("%s",Command);
        if (strcmp(Command,"tree")==0)
            return 9;
        if (strcmp(Command,"left")==0){
            scanf("%s",Command);
            if (strcmp(Command,"parent")==0){
                scanf("%d",TempInt2);
                return 10;
            }
        }
        if (strcmp(Command,"right")==0){
            scanf("%s",Command);
            if (strcmp(Command,"parent")==0){
                scanf("%d",TempInt2);
                return 11;
            }
        }
        if (strcmp(Command,"sibling")==0){
            scanf("%d",TempInt2);
            return 12;
        }
    }
    return -1;
}

//Втоаря часть функции по обработке комманд
int CommandCheck(int TempNum1,int TempNum2,int TempNum3,int TempNum4,int *TempInt1,int *TempInt2){
    char Command[255];
    scanf("%s",Command);
    if (strcmp(Command,"root")==0){
        scanf("%d",TempInt1);
        return TempNum1;
    }
    if (strcmp(Command,"node")==0){
        scanf("%d",TempInt1);
        scanf("%s",Command);
        if (strcmp(Command,"left")==0){
            scanf("%s",Command);
            if (strcmp(Command,"parent")==0){
                scanf("%d",TempInt2);
                return TempNum2;
            }
        }
        if (strcmp(Command,"right")==0){
            scanf("%s",Command);
            if (strcmp(Command,"parent")==0){
                scanf("%d",TempInt2);
                return TempNum3;
            }
        }
        if (strcmp(Command,"sibling")==0){
            scanf("%d",TempInt2);
            return TempNum4;
        }
    }
    return -1;
}

//Добавление элемента в дерево
TypeTree *AddTree(TypeTree *Tree,int Elem){
	if (Tree==NULL){ //Создаем поддерево с ветками
		Tree=(TypeTree*)malloc(sizeof(TypeTree)); //Выделяем память под поддерево
		Tree->Key=Elem; //Кладем ключ в поддерево
		Tree->Left=NULL;
		Tree->Right=NULL;
	}
	return Tree; //Возвращаем указатель на дерево
}

//Освобождение памяти из под дерева
void FreeTree(TypeTree *Tree){
	if (Tree!=NULL){
		FreeTree(Tree->Left);
		FreeTree(Tree->Right);
		free(Tree);
	}
}

//Функция для поиска нужного элемента
TypeTree* TreeSearch(TypeTree* Tree,int SearchNum,int TypeSearch,int flag){
    static TypeTree *SearchTree;
    TypeTree *TempTree;
    if (flag==1)
        SearchTree=NULL;
    if (Tree!=NULL){
        if (Tree->Key==SearchNum){ //Условия на искомый элемент
            if ((TypeSearch==1)&&(Tree->Left==NULL))
                SearchTree=Tree;
            if ((TypeSearch==2)&&(Tree->Right==NULL))
                SearchTree=Tree;
            if ((TypeSearch==3)&&((Tree->Back!=NULL)))
                if ((Tree->Back->Left==NULL)||(Tree->Back->Right==NULL))
                    SearchTree=Tree;
            if ((TypeSearch==4)&&(Tree->Left!=NULL))
                SearchTree=Tree;
            if ((TypeSearch==5)&&(Tree->Right!=NULL))
                SearchTree=Tree;
            if ((TypeSearch==6)&&(Tree->Back!=NULL)){
                if ((Tree->Back->Left==Tree)&&(Tree->Back->Right!=NULL))
                    SearchTree=Tree->Back->Right;
                if ((Tree->Back->Right==Tree)&&(Tree->Back->Left!=NULL))
                    SearchTree=Tree->Back->Left;
            }
        }
        TempTree=TreeSearch(Tree->Left,SearchNum,TypeSearch,0); //Обход в глубину
        TempTree=TreeSearch(Tree->Right,SearchNum,TypeSearch,0);
    }
    if (flag==1)
        return SearchTree; //Возвращаем указатель на элемент
    return Tree;

}

//Выводим дерeво на консоль
void PrintTree(TypeTree *Tree,int level){
    int i;
    if(Tree!=NULL){
        PrintTree(Tree->Right,level+1);
        for (i=0;i<level;i++)
            printf("    ");
        printf("%d\n",Tree->Key);
        PrintTree(Tree->Left,level+1);
    }
}

//Сохраняем структуры в файл
void SaveFile(TypeTree *Tree,FILE **openFile){
    if (Tree!=NULL){
        fwrite(Tree,sizeof(TypeTree),1,*openFile);
        if (Tree->Left!=NULL)
            SaveFile(Tree->Left,openFile);
        if (Tree->Right!=NULL)
            SaveFile(Tree->Right,openFile);
    }
}

//Загружаем структуры из файла
void LoadFile(TypeTree **Tree,FILE **openFile){
    if (!feof(*openFile)){
        (*Tree)=(TypeTree*)malloc(sizeof(TypeTree));
        fread(*Tree,sizeof(TypeTree),1,*openFile);
        if ((*Tree)->Left!=NULL)
            LoadFile(&((*Tree)->Left),openFile);
        if ((*Tree)->Right!=NULL)
            LoadFile(&((*Tree)->Right),openFile);
    }
}

//Анализируем дерево
void Analysis(TypeTree *Tree,int flag){
    static int leaf=0,node=0,heap=1;
    if (flag==1){
        leaf=0;
        node=0;
        heap=1;
    }
    if (Tree!=NULL){
        node++;
        if ((Tree->Left!=NULL)&&(Tree->Left->Key>Tree->Key))
            heap=0;
        if ((Tree->Right!=NULL)&&(Tree->Right->Key>Tree->Key))
            heap=0;
        if (Tree->Left!=NULL)
            Analysis(Tree->Left,0);
        if (Tree->Right!=NULL)
            Analysis(Tree->Right,0);
        if ((Tree->Left==NULL)&&(Tree->Right==NULL))
            leaf++;
    }
    if (flag==1)
        printf("Leaf==%d\nNode==%d\nAll node==%d\nHeap==%d\n",leaf,node,node-leaf,heap);
}

//Восстанавливаем указатели в загруженном дереве
void BackPtr(TypeTree *Tree,TypeTree *ptr){
    if (Tree!=NULL){
        Tree->Back=ptr;
        BackPtr(Tree->Left,Tree);
        BackPtr(Tree->Right,Tree);
    }
}
