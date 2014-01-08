package com.alexanderdbrown.abstract_data_types.linked_lists;

public class SinglyLinkedListNode<E> {
	E element;
	SinglyLinkedListNode<E> next;
	
	SinglyLinkedListNode(E element) {
		this.element = element;
		next = null;
	}
	
	boolean hasNext() {
		return next != null;
	}
}
