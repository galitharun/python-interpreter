#include<iostream>
using namespace std;
#include"Kyser1.h"
#include"Header.h"
void print(KyObject *kob){
	if (strcmp(kob->getType().c_str(), "int") == 0)
	{
		KyInt *i = (KyInt*)kob;
		cout << i->kyint;
	}
	else if (strcmp(kob->getType().c_str(), "string") == 0){
		KyString *s = (KyString*)kob;
		cout << "'" << s->kystring << "'";
	}
	else if (strcmp(kob->getType().c_str(), "list") == 0)
	{
		KyList *l = (KyList*)kob;
		KyObject *temp;
		cout << "[";
		for (int i = 0; i < l->length; i++)
		{	
			temp=(KyObject*)l->kylist[i];
			print(temp);
			if (i != l->length - 1)
			cout << ",";
		}
		cout << "]";
	}
	else if (strcmp(kob->getType().c_str(), "dict") == 0){
		KyDict *d = (KyDict*)kob;
		cout << "{";
		for (int i = 0; i < d->length; i++)
		{
			print((KyObject*)d->key[i]);
			cout << ":";
			print((KyObject*)d->value[i]);
			if (i != d->length - 1)
			cout << ",";

		}
		cout << "}";
	}
}
KyObject* parse(string filename)
{
	string file = readFile(filename);
	KyObject *obj[10],*obj2[10];
	char str[50];
	int i = 0, top = 0,obj_index,obj2_index,value;
	KyObject *memory[100];
	KyObject *stack[100];
	KyInt *in;
	KyString *ks;
	KyDict *kd;
	KyList *kl;
	KyMarker *km;
	while (file[i])
	{
		int pos;
		value = 0;
		obj_index = 0;
		obj2_index = 0;
		kd = new KyDict();
		kl = new KyList();
		km = new KyMarker();
		switch (file[i])
		{
		case 'a':
			top = top - 1;
			kl = (KyList*)stack[top-1];
			kl->append(stack[top]);
			

			break;
		case 'e':
			top = top - 1;
			while (strcmp(stack[top]->getType().c_str(), "marker") != 0)
			{
				obj[obj_index++] = stack[top--];
			}
			top--;
			kl = (KyList*)stack[top];
			for (int j = 0; j < obj_index; j++)
			{
				kl->append(obj[j]);

			}
			
			stack[top++] = kl;
			break;
		case 'l':
			top = top - 1;
			while (strcmp(stack[top]->getType().c_str(), "marker") != 0)
			{
				obj[obj_index++] = stack[top--];
			}

			for (int j = 0; j < obj_index; j++)
			{
				kl->append(obj[j]);

			}
			stack[top] = kl;
			top++;
			break;
		case 'S':
			i=i+2;
			while (file[i] != '\n')
			{
				str[obj_index++] = file[i++];
			}
			str[obj_index - 1] = '\0';
			ks =new KyString(str);
			stack[top++] = ks;
			break;
		case '}':
			stack[top++] = kd;
			break;
		case 'd':
			top = top - 1;
			while (strcmp(stack[top]->getType().c_str(), "marker") != 0)
			{
				obj[obj_index] = stack[top--];
				obj2[obj2_index] = stack[top--];
				kd->set(obj[obj_index], obj2[obj2_index]);
				obj_index++, obj2_index++;
			}
			stack[top] = kd;
			top++;
			break;
		case 's':
			top = top - 1;
			while (strcmp(stack[top]->getType().c_str(), "dict") != 0)
			{
				obj[obj_index++] = stack[top--];
				obj2[obj2_index++] = stack[top--];
			}
			kd = (KyDict*)stack[top];
			for (int j = 0; j < obj_index; j++)
			{
				kd->set(obj[j], obj2[j]);
			}
			stack[top++] = kd;
			break;
		case 'u':
			top = top - 1;
			while (strcmp(stack[top]->getType().c_str(), "marker") != 0)
			{
				obj[obj_index++] = stack[top--];
				obj2[obj2_index++] = stack[top--];
			}
			top--;
			kd = (KyDict*)stack[top];
			for (int j = 0; j < obj_index; j++)
			{
				kd->set(obj[j], obj2[j]);
			}
			stack[top++] = kd;
			break;
		case '(':
			stack[top++] = km;
			break;
		case '.':
			top = top - 1;
			print(stack[top]);
			return stack[top--];
			break;
		case 'p':
			i++;
			pos = file[i]-'0';
			memory[pos] = stack[top-1];
			break;
		case 'g':
			i++;
			pos = file[i] - '0';
			stack[top++] = memory[pos];
			break;
		case 'I':
			i++;
			while (file[i] != '\n')
			{
				value *= 10;
				value += file[i] - '0';
				i++;
			}
			in = new KyInt(value);
			stack[top++] = in;
		default:break;
		}
		i++;
	}
	
}