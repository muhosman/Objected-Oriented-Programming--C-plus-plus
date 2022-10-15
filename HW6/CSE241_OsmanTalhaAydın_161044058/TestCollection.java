/**
* Bu bir JavaDoc Örneğidir.
*
* @author Osman Talha Aydın
*/


interface Collection<E>
{
	Iterator<E> iterator();
	void add(E e);
	void addAll(Collection c);
	void clear();
	boolean contains(E e);
	boolean containsAll(Collection c);
	boolean isEmpty();
	void remove(E e);
	void removeAll(Collection c);
	void retainAll(Collection c);
	int size();
}


interface Set<E> extends Collection<E>
{
}

interface List<E> extends Collection<E>
{
	void add(int inde,E e);
	void remove(int inde);
	E get(int inde);
}

interface Queue<E> extends Collection<E>
{
	void offer(E e);
	E pool();
	E element();
}


class HashSet<E> implements Set<E>
{
	private E []set;
  private int counter;
	private int index;

	int getcounter()
	{return counter;}
	int getindex()
	{return index;}

  public HashSet()
  {
    set = (E[])new Object[1];
    counter = 0;
		index = 0;
  }
	public void add(E e)
	{
		int flag = 0;
		E []temp = null;

		for (int i=0;i<size() ;++i ) {
			if (set[i] == e) {
				flag=1;
				break;
			}
		}
		if (flag == 0) {
			temp = (E[])new Object[counter+2];
			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter]=e;
			counter++;
		}

	}

	public void addAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			add(t.next());
		}
	}

	public void clear()
  {
		for (int i=0;i<size();i++ ) {
			set[i] = null;
		}
		counter = 0;
		index = 0;
  }

  public boolean contains(E e)
  {
		for (int i = 0; i<size(); i++)
		{
			if (set[i].equals(e)) {
				return true;
			}
		}
		return false;
  }

	public boolean containsAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		while(t.hasNext())
		{
			if(!contains(t.next()))
				return false;
		}
		return true;
	}

  public boolean isEmpty()
	{
		if (set[0] == null) {
			return true;
		}
		return false;
	}

	public void remove(E e)
	{
		if (counter > 0)
		{
			for (int i=0;i<size();i++ ) {
				if (set[i].equals(e)) {
					index = i;
					break;
				}
			}
			for (int i = index; i<size(); i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
	}

	public void removeAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			remove(t.next());
			counter--;
		}
	}
	public void retainAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		E []temp = null;

		clear();

		while(t.hasNext())
		{
			temp = (E[])new Object[counter+2];

			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter] = t.next();
			counter++;
		}
	}


	public int size()
	{
		return counter;
	}

	public Iterator<E> iterator()
	{
		return new myIterator();
	}

	class myIterator implements Iterator
	{
		int count;
		public myIterator()
		{
			count=0;
		}
		public boolean hasNext()
		{
			if(set[count] == null){
				return false;
			}
			return true;
		}
		public E next()
		{
			if (hasNext()) {
				return set[count++];
			}
			return null;
		}
		public void remove()
		{
			count--;
			if (hasNext()) {

				if (count > 0)
				{
					for (int i = count; set[i] != null; i++)
					{
						set[i] = set[i + 1];
					}
				}
			}
		}
	}

}

class ArrayList<E> implements List<E>
{
	private E []set;
	private int counter;
	private int index;

	public ArrayList()
	{
		set = (E[])new Object[1];
		counter = 0;
		index = 0;
	}
	public E get(int inde)
	{
		return set[inde];
	}
	public void add(E e)
	{
		E []temp = null;

			temp = (E[])new Object[counter+2];
			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter]=e;
			counter++;

	}
	public void add(int inde,E e)
	{
		E []temp = null;
		if (set[inde] != null) {
			temp = (E[])new Object[size()+2];
			for (int i = 0; i < size(); i++)
			{
				if (inde == i) {
					temp[inde] = e;
				}
				else
					temp[i] = set[i];
			}
			set =temp;
		}
		else if (inde == size()) {
			temp = (E[])new Object[size()+2];
			for (int i = 0; i < size(); i++)
			{
				temp[i] = set[i];
			}
			set =temp;
			set[inde] = e;
			counter++;
		}
	}


	public void addAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			add(t.next());
		}
	}

	public void clear()
  {
		for (int i=0;i<size();i++ ) {
			set[i] = null;
		}
		counter = 0;
		index = 0;
  }

  public boolean contains(E e)
  {
		for (int i = 0; i<size(); i++)
		{
			if (set[i].equals(e)) {
				return true;
			}
		}
		return false;
  }

	public boolean containsAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		while(t.hasNext())
		{
			if(!contains(t.next()))
				return false;
		}
		return true;
	}

	public boolean isEmpty()
	{
		if (counter == 0) {
			return true;
		}
		return false;
	}

	public void remove(E e)
	{
		if (counter > 0)
		{
			for (int i=0;i<size();i++ ) {
				if (set[i].equals(e)) {
					index = i;
					break;
				}
			}
			for (int i = index; i<size(); i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
	}

	public void remove(int inde)
	{
		if (counter > 0 && set[inde] != null)
		{
			for (int i = inde; set[i] != null; i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
	}
	public void removeAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			remove(t.next());
			counter--;
		}
	}
	public void retainAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		E []temp = null;

		clear();

		while(t.hasNext())
		{
			temp = (E[])new Object[counter+2];

			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter] = t.next();
			counter++;
		}
	}


	public int size()
	{
		return counter;
	}

	public Iterator<E> iterator()
	{
		return new myIterator();
	}

	class myIterator implements Iterator
	{
		int count;
		public myIterator()
		{
			count=0;
		}
		public boolean hasNext()
		{
			if(set[count] == null){
				return false;
			}
			return true;
		}
		public E next()
		{
			if (hasNext()) {
				return set[count++];
			}
			return null;
		}
		public void remove()
		{
			count--;
			if (hasNext()) {

				if (count > 0)
				{
					for (int i = count; set[i] != null; i++)
					{
						set[i] = set[i + 1];
					}
				}
			}
		}
	}
}
class LinkedList<E> implements List<E>,Queue<E>
{
	private E []set;
	private int counter;
	private int index;

	public LinkedList()
	{
		set = (E[])new Object[1];
		counter = 0;
		index = 0;
	}
	public void offer(E e)
	{
		add(e);
	}
	public E pool()
	{
		E t=null;
		if (counter > 0)
		{
			t = set[0];
			for (int i = 0; set[i] != null; i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
		return t;
	}
	public E element()
	{
		return set[0];
	}

	public E get(int inde)
	{
		return set[inde];
	}
	public void add(E e)
	{
		E []temp = null;

			temp = (E[])new Object[counter+2];
			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter]=e;
			counter++;


	}
	public void add(int inde,E e)
	{
		E []temp = null;
		if (set[inde] != null) {
			set[inde] = e;
		}
		else if (inde == size()) {
			temp = (E[])new Object[size()+2];
			for (int i = 0; i < size(); i++)
			{
				temp[i] = set[i];
			}
			set =temp;
			set[inde] = e;
			counter++;
		}
	}


	public void addAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			add(t.next());
		}
	}

	public void clear()
  {
		for (int i=0;i<size();i++ ) {
			set[i] = null;
		}
		counter = 0;
		index = 0;
  }

  public boolean contains(E e)
  {
		for (int i = 0; i<size(); i++)
		{
			if (set[i].equals(e)) {
				return true;
			}
		}
		return false;
  }

	public boolean containsAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		while(t.hasNext())
		{
			if(!contains(t.next()))
				return false;
		}
		return true;
	}

	public boolean isEmpty()
	{
		if (counter == 0) {
			return true;
		}
		return false;
	}

	public void remove(E e)
	{
		if (counter > 0)
		{
			for (int i=0;i<size();i++ ) {
				if (set[i].equals(e)) {
					index = i;
					break;
				}
			}
			for (int i = index; i<size(); i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
	}

	public void remove(int inde)
	{
		if (counter > 0 && set[inde] != null)
		{
			for (int i = inde; set[i] != null; i++)
			{
				set[i] = set[i + 1];
			}
			counter--;
		}
	}
	public void removeAll(Collection c)
	{
		Iterator<E> t = c.iterator();

		while(t.hasNext())
		{
			remove(t.next());
			counter--;
		}
	}
	public void retainAll(Collection c)
	{
		Iterator<E> t = c.iterator();
		E []temp = null;

		clear();

		while(t.hasNext())
		{
			temp = (E[])new Object[counter+2];

			for (int i = 0; i<size(); i++)
			{
				temp[i] = set[i];
			}
			set = temp;
			set[counter] = t.next();
			counter++;
		}
	}


	public int size()
	{
		return counter;
	}

	public Iterator<E> iterator()
	{
		return new myIterator();
	}

	class myIterator implements Iterator
	{
		int count;
		public myIterator()
		{
			count=0;
		}
		public boolean hasNext()
		{
			if(set[count] == null){
				return false;
			}
			return true;
		}
		public E next()
		{
			if (hasNext()) {
				return set[count++];
			}
			return null;
		}
		public void remove()
		{
			count--;
			if (hasNext()) {

				if (count > 0)
				{
					for (int i = count; set[i] != null; i++)
					{
						set[i] = set[i + 1];
					}
				}
			}
		}
	}
}

interface Iterator<E>
{
	boolean hasNext();
	E next();
	void remove();
}

public class TestCollection
{
	public static void main(String []args)
	{
		System.out.printf("\nI tested all method one time. And I prepared two option.You can remove both slash\nForexample remove 687-688 slash and put 684-685.Afterthat remove 702-779 And put slash the hashset Integer test.\nYou can test with string type.\n");

		HashSet<String> set = new HashSet<String>();
		HashSet<String> set1 = new HashSet<String>();

		//	HashSet<Integer> set = new HashSet<Integer>();
		//	HashSet<Integer> set1 = new HashSet<Integer>();

		//ArrayList<String> array = new ArrayList<String>();
		//ArrayList<String> array1 = new ArrayList<String>();

		ArrayList<Integer> array = new ArrayList<Integer>();
		ArrayList<Integer> array1 = new ArrayList<Integer>();

		LinkedList<String> list = new LinkedList<String>();



		try
		{
			/*
			//HashSet(INTEGER) Test
			System.out.printf("\nHASH SET TEST (INTEGER) //////////////////\n");

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is empty.\n\n");
			}

			set.add(3);
			set.add(4);
			set.add(5);
			set.add(1);
			set.add(2);

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is not empty.\n\n");
			}

			set1.addAll(set);

			Iterator<Integer> temp = set.iterator();
			Integer str;
			while(temp.hasNext())
			{
				str = (Integer)temp.next();
				if (str.equals(5)) {
					temp.remove();
				}
			}
			set1.remove(4);


			Iterator<Integer> t0 = set1.iterator();
			while(t0.hasNext())
			{
				System.out.println("set1 -- HashSet element:"+t0.next());
			}
			System.out.printf("\n");

			Iterator<Integer> t1 = set.iterator();
			while(t1.hasNext())
			{
				System.out.println("set -- HashSet element:"+t1.next());
			}

			set.retainAll(set1);
			System.out.printf("\nset.retainAll(set1) OPERATION\n");
			Iterator<Integer> t = set.iterator();
			while(t.hasNext())
			{
				System.out.println("set -- HashSet element:"+t.next());
			}

			if (set1.contains(1)) {
				System.out.printf("It contains.\n\n");
			}

			if (!set.containsAll(set1)) {
				System.out.printf("It doesn't contains all element.\n\n");
			}
			set.clear();

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is empty.\n\n");
			}
*/


			//HashSet(STRING) Test

			System.out.printf("\nHASH SET TEST (String) //////////////////\n");

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is empty.\n\n");
			}

			set.add("Osman");
			set.add("Osman1");
			set.add("Osman2");
			set.add("Osman3");
			set.add("Osman4");
			set.add("Osman5");

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is not empty.\n\n");
			}

			set1.addAll(set);

			Iterator<String> temp = set.iterator();
			String str="";
			while(temp.hasNext())
			{
				str = (String)temp.next();
				if (str.equals("Osman2")) {
					temp.remove();
				}
			}
			set1.remove("Osman4");


			Iterator<String> t0 = set1.iterator();
			while(t0.hasNext())
			{
				System.out.println("set1 -- HashSet element:"+t0.next());
			}
			System.out.printf("\n");

			Iterator<String> t1 = set.iterator();
			while(t1.hasNext())
			{
				System.out.println("set -- HashSet element:"+t1.next());
			}

			set.retainAll(set1);
			System.out.printf("\nset.retainAll(set1) OPERATION\n");
			Iterator<String> t = set.iterator();
			while(t.hasNext())
			{
				System.out.println("set -- HashSet element:"+t.next());
			}

			if (set1.contains("Osman3")) {
				System.out.printf("It contains.\n\n");
			}

			if (!set.containsAll(set1)) {
				System.out.printf("It doesn't contains all element.\n\n");
			}
			set.clear();

			if (set.isEmpty()) {
				System.out.printf("\nSet is empty.\n\n");
			}
			else
			{
				System.out.printf("\nSet is empty.\n\n");
			}

			//Array List(INTEGER) Test
			System.out.printf("\nARRAY LIST(INTEGER) TEST //////////////////\n\n");
			array.add(0,3);
			array.add(1,4);
			array.add(2,5);
			array.add(3,1);

			array1.addAll(array);


			array.remove(1);
			for (int i=0;array.get(i) != null ;++i ) {
				System.out.println("Array "+i+":"+array.get(i));
			}
			System.out.printf("\n");
			for (int i=0;array1.get(i) != null ;++i ) {
				System.out.println("Array1 "+i+":"+array1.get(i));
			}

			array1.add(1,8);

			System.out.printf("\nI changed array1 index=1 1 to 8.\n");
			for (int i=0;array1.get(i) != null ;++i ) {
				System.out.println("Array1 "+i+":"+array1.get(i));
			}
			//Array List(STRING) Test
			/*
			System.out.printf("\nARRAY LIST(STRING) TEST //////////////////\n\n");
			array.add(0,"Talha");
			array.add(1,"Talha1");
			array.add(2,"Talha2");
			array.add(3,"Talha3");

			array1.addAll(array);


			array.remove(1);
			for (int i=0;array.get(i) != null ;++i ) {
				System.out.println("Array "+i+":"+array.get(i));
			}
			System.out.printf("\n");
			for (int i=0;array1.get(i) != null ;++i ) {
				System.out.println("Array "+i+":"+array1.get(i));
			}
*/
			//LINKED List Test
			System.out.printf("\nLINKED LIST TEST //////////////////\n\n");

			list.offer("Osman");
			list.offer("Osman2");
			list.offer("Osman3");
			list.offer("Osman4");
			list.offer("Osman5");
			list.offer("Osman4");

			System.out.printf("\n");
			for (int i=0;list.get(i) != null ;++i ) {
				System.out.println("List "+i+":"+list.get(i));
			}
			System.out.println("\nList (poll):"+list.pool());
			System.out.printf("\n");
			for (int i=0;list.get(i) != null ;++i ) {
				System.out.println("List "+i+":"+list.get(i));
			}
			System.out.println("\nList (element):"+list.element());
			System.out.printf("\n");
			for (int i=0;list.get(i) != null ;++i ) {
				System.out.println("List "+i+":"+list.get(i));
			}
		}
		catch(Exception e) {
			System.out.println(e.toString());
		}
	}

}
