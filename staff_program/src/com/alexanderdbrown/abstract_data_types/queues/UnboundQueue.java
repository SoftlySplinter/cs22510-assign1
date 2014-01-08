package com.alexanderdbrown.abstract_data_types.queues;

import com.alexanderdbrown.abstract_data_types.linked_lists.DoublyLinkedList;
import com.alexanderdbrown.abstract_data_types.linked_lists.LinkedList;

/**
 * The implementation of a {@link Queue} which uses the 
 * {@link LinkedList} (specifically the {@link DoublyLinkedList}) 
 * ADT so the Queue has no boundaries (theoretically at least, in
 * practise this is actually limited by the amount of memory 
 * available to the JVM).
 * <p>
 * Recently changed to use Generics instead of 
 * {@link Object Objects}, allowing the implementation and usage
 * of this class to be more strict.
 * 
 * @author Alexander Brown
 * @version 2.0
 */
public class UnboundQueue<E> implements Queue<E> {
	LinkedList<E> queue = new DoublyLinkedList<E>();
	
	@Override
	public void insert(E element) {
		queue.insertToTail(element);
	}

	@Override
	public E remove() {
		try {
			return queue.remove();
		} catch(ArrayIndexOutOfBoundsException e) {
			throw e;
		}
	}
	
	@Override
	public E getTop() {
		try {
			return queue.get();
		} catch(ArrayIndexOutOfBoundsException e) {
			throw e;
		}
	}

	@Override
	public boolean isEmpty() {
		return queue.isEmpty();
	}

	@Override
	public int length() {
		return queue.length();
	}
	
}
