package com.alexanderdbrown.abstract_data_types.linked_lists;

public interface LinkedList<E> {
	
	public void insert(E element);
	
	public void insert(E element, int index);
	
	public void insertToTail(E element);
	
	public E remove();
	
	public E remove(int index);
	
	public E removeFromTail();

	public E get();
	
	public E get(int index);
	
	public E getFromTail();
	
	public int length();
	
	public boolean isEmpty();
}
