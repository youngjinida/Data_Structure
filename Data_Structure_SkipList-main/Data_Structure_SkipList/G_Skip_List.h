#ifndef GENERIC_SKIP_LIST_H
#define GENERIC_SKIP_LIST_H

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#define PROBABILITY_OF_ABOVE_LEVEL 2
#define PLUS_INF INT_MAX
#define MINUS_INF INT_MIN

using namespace std;

template<typename K, typename V>
class SkipList
{
protected:
	class QuadNode
	{
	public:
		QuadNode(K k, V v)
			:_key(k), _value(v)
		{
			up = down = prev = next = NULL;
			level = -1;
		}
		QuadNode() {}
		~QuadNode() {}
		K& getKey() { return _key; }
		V& getValue() { return _value; }
		void setKey(K k) { _key = k; }
		void setValue(V v) { _value = v; }
		friend class Position;
	protected:
		QuadNode* up;
		QuadNode* down;
		QuadNode* prev;
		QuadNode* next;
		int level;
	private:
		K _key;
		V _value;
	};
public:
	class Position
	{
		friend class SkipList;
	public:
		Position(QuadNode* pSLN) { pQN = pSLN; }
		Position() {}
		~Position() {}
		K& getKey() { return pQN->getKey(); }
		V& getValue() { return pQN->getValue(); }
		Position above() { return Position(pQN->up); }
		Position below() { return Position(pQN->down); }
		Position after() { return Position(pQN->next); }
		Position before() { return Position(pQN->prev); }
		void setabove(const Position& p) { pQN->up = p.pQN; }
		void setbelow(const Position& p) { pQN->down = p.pQN; }
		void setafter(const Position& p) { pQN->next = p.pQN; }
		void setbefore(const Position& p) { pQN->prev = p.pQN; }
		bool operator==(const Position& q)const { return (pQN == q.pQN); }
		bool operator!=(const Position& q)const { return (pQN != q.pQN); }
		V& operator*() {
			return pQN->getValue();
		}
	protected:
		QuadNode* pQN;
	};
private:
	Position start;
	Position end;
	int height;
	int num_element;
public:
	SkipList()
	{
		height = 0;											// ó�� ���̴� 0
		num_element = 0;									// ������ ó�� ������ 0��
		QuadNode* pQNode = new QuadNode(K(MINUS_INF), V()); // Ű���� �����ϴ� -oo ������ �߰�
		start = Position(pQNode);							// start�� ����
		pQNode = new QuadNode(K(PLUS_INF), V());			// Ű���� �����ϴ� oo ������ �߰�
		end = Position(pQNode);								// end�� ����

		start.setafter(end);								// ����
		start.setbefore(Position(NULL));
		start.setabove(Position(NULL));
		start.setbelow(Position(NULL));

		end.setafter(Position(NULL));
		end.setbefore(start);								// ����
		end.setabove(Position(NULL));
		end.setbelow(Position(NULL));

		srand(time(NULL));									// ���� ������ ����
	}
	~SkipList() {};
	Position SkipListSearch(K& k)
	{
		Position pos = this->start;
		while (pos.below() != Position(NULL))
		{
			pos = pos.below();
			while (k >= (pos.after()).getKey())
			{
				pos = pos.after();
				if (pos.after() == (Position(NULL)))
					break;
			}
		}
		return pos;
	}
	
	Position SkipListInsert(ostream& fout, K k, const V v)
	{
		Position p, q, t;
		p = SkipListSearch(k);				// ���� k�� v�� �� Position ����
		q = Position(NULL);					// temp ����
		int i = -1;							// ���� ����
		do
		{
			i = i + 1;
			if (i >= height)				// ���ο� �� ����
			{
				height = height + 1;
				t = start.after();			// start�� ������ ����Ű�� ����
				start = InsertAfterAbove(fout, Position(NULL), start, MINUS_INF, V()); 
					// start �Ʒ��� MINUS_INF�� Ű�� ���� ��带 ����
					// �׸��� ��ŸƮ �ڸ��� ����
				InsertAfterAbove(fout, start, t, PLUS_INF, V());					
			} // ���� ���̱�
			q = InsertAfterAbove(fout, p, q, k, v); // ó�� ������ ���� q�� NULL������ �ι�°�� NULL�� �ƴ϶� ��!
			while (p.above() == Position(NULL))
			{
				p = p.before();
			}
			p = p.above();
			//q = InsertAfterAbove(fout, p, q, k, v);
			//PrintSkipList(fout);
		} while (rand() % 2 == 0);
		++num_element;
		return q;
	}
	Position InsertAfterAbove(ostream& fout, Position p, Position q, const K k, const V v)
		// p --- newNode(k,v) --- NULL
		//			|
		//          q
	{
		QuadNode* pNewNode = new QuadNode(k, v); // ���� K, V���� �̿��ؼ� �� ��带 ����
		Position n(pNewNode);					// �� ����� �������� ���
		n.setabove(Position(NULL));				// ��, �Ʒ�, ��,�� NULL �� ���
		n.setbelow(Position(NULL));
		n.setafter(Position(NULL));
		n.setbefore(Position(NULL));
		if (p == Position(NULL))				// ���� p�� NULL �ϰ��
		{
			if (q == Position(NULL))			// NULL�� NULL�� �����غ��� �ǹ̰� ����!
			{
				fout << "Trying to insert at";
				fout << "(NULL, NULL) position\n";
				return Position(NULL);
			}
			else
			{
				q.setabove(n);					// ������ ���� n�� q�� ���Ʒ��� �̾��ִ� ��
				n.setbelow(q);					
				n.setabove(Position(NULL));
				n.setafter(Position(NULL));
				return n;
			}
		}
		else
		{
			if (q == Position(NULL))
			{
				Position nx, ny;
				fout << "insert a node (" << n.getKey();
				fout << ") at level 0\n";
				nx = p.after();
				p.setafter(n);
				n.setbefore(p);
				n.setafter(nx);
				nx.setbefore(n);
				n.setbelow(Position(NULL));
				n.setabove(Position(NULL));
				return n;
			}
			else
			{
				Position nx, ny;
				nx = p.after();					// nx�� p�� ������ ����Ŵ
				n.setafter(nx);					// n�� ������ nx
				if (nx != Position(NULL))
					nx.setbefore(n);
				p.setafter(n);					
				n.setbefore(p);					// n�� p�� ������ ����
				ny = q.above();					// ny�� q�� ���� ����Ŵ
				q.setabove(n);					// n�� q�� �� �Ʒ��� ����
				n.setbelow(q);
				n.setabove(ny);					// n�� ���� p�� ���� ��
				if (ny != Position(NULL))
					ny.setbelow(n);
			}
		}
		return n;
	}
	void SkipListNodeDelete(Position p)
	{
		Position pprev, pnext;
		if (p != Position(NULL))
		{
			pprev = p.before();
			pnext = p.after();
			if (pprev != Position(NULL))
				pprev.setafter(pnext);
			if (pnext != Position(NULL))
				pnext.setbefore(pprev);
			delete p.pQN;
		}
	}
	void SkipListRemove(ostream& fout, K k)
	{
		Position p, pprev, pnext, p00, px0;
		Position p0y, pxy, old_p;
		int h_max, h;
		p = SkipListSearch(k);
		if ((p.getKey() != k) || (p.getKey() == PLUS_INF))
		{
			fout << "Key (" << k << ") is not found in SkipList\n";
			return;
		}
		while (p != Position(NULL))
		{
			old_p = p;
			p = p.above();
			SkipListNodeDelete(old_p);
			//PrintSkipList(fout);
		}
		fout << "Delete SkipList node(Key:" << k << ")\n";
		p00 = start;
		for (int i = height; i > 0; i--)
		{
			p00 = p00.below();
		}
		px0 = p00.after();
		pxy = start;
		h_max = 0;
		while (px0.getKey() != PLUS_INF)
		{
			pxy = px0;
			h = 0;
			while (pxy != Position(NULL))
			{
				++h;
				pxy = pxy.above();
			}
			if (h_max < h)
				h_max = h;
			px0 = px0.after();
		}
		if (h_max < height)
		{
			fout << "Current height is less than";
			fout << "the new h_max (" << h_max;
			fout << ") ==> need adjustment !!\n";
		}
		for (int i = 0; i < (height - h_max); i++)
		{
			p0y = start;
			pxy = start.after();
			start = start.below();
			SkipListNodeDelete(pxy);
			SkipListNodeDelete(p0y);
		}
		height = h_max;
	}
	void PrintSkipList(ostream& fout)
	{
		Position p, p00, px0, p0y, pxy, q, q0, qx;
		int level;
		fout << "Print SkipList Inside:";
		fout << "current height (" << height << ")\n";
		p00 = start;
		level = height;
		for (int i = height; i > 0; --i)
		{
			p00 = p00.below();
		}

		p0y = start;
		pxy = start;
		for (level = height; level >= 0; level--)
		{
			fout << "level" << setw(2) << level << " ";
			if (pxy.getKey() == MINUS_INF)
				fout << "-oo";
			else
				fout << setw(5) << pxy.getKey();

			px0 = p00.after();
			for (pxy = p0y.after();; pxy = pxy.after())
			{
				while (px0.getKey() != pxy.getKey())
				{
					fout << " ------";
					px0 = px0.after();
				}
				if (pxy.getKey() == PLUS_INF)
					break;
				else
					fout << " -" << setw(5) << pxy.getKey();
				px0 = px0.after();
			}
			if (pxy.getKey() == PLUS_INF)
				fout << "\ +oo";
			else
				fout << setw(5) << pxy.getKey();
			fout << "\n";
			p0y = p0y.below();
			pxy = p0y;
		}
		fout << "\n";
	}
};

#endif // !GENERIC_SKIP_LIST_H

