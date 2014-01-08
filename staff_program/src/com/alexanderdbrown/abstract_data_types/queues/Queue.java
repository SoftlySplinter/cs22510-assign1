package com.alexanderdbrown.abstract_data_types.queues;

/**
 * Defines the interface for the Queue Abstract Data Type.
 * <p>
 * The Queue ADT uses the First in, First out (FIFO) model, where
 * the first element that was added to the Queue will be the 
 * first one that is removed (like a real queue, each element 
 * 'waits' their turn in the Queue).
 * <p>
 * Recently changed to use Generics instead of 
 * {@link Object Objects}, allowing the implementation and usage
 * of this class to be more strict.
 * 
 * @see BoundQueue
 * @see UnboundQueue
 * 
 * @author Alexander Brown
 * @version 2.0 (2011-02-17)
 *
 */
public interface Queue<E> {
	static final int DEFAULT_QUEUE_SIZE = 25;
	
	/**
	 * Inserts an element to the top of the Queue
	 * @param element
	 */
	public void insert(E element);
	
	/**
	 * Returns and removes the top element in the Queue.
	 * @return The top element of the Queue.
	 */
	public E remove();
	
	/**
	 * Returns the top element of the Queue without removing it.
	 * @return The top element of the Queue without removing it.
	 */
	public E getTop();
	
	/**
	 * Returns the Length of the Queue.
	 * @return The length of the Queue.
	 */
	public int length();
	
	/**
	 * Returns <code>true</code> if the Queue is empty.
	 * @return <code>true</code> - If the Queue is empty.
	 */
	public boolean isEmpty();
}
