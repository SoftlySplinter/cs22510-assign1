package com.alexanderdbrown.abstract_data_types.linked_lists;

/**
 * Runtime Exception thrown when a Linked List Index is out of bounds.
 * @author softly
 *
 */
public class LinkedListIndexOutOfBoundsException extends RuntimeException {
	private static final long serialVersionUID = 5565478598505500668L;
	
	LinkedListIndexOutOfBoundsException(int index) {
		super(index+"");
	}
}
