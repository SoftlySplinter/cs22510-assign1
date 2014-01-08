package com.alexanderdbrown.abstract_data_types.linked_lists;

public class DoublyLinkedListNode<E> {
	E element;
	DoublyLinkedListNode<E> next;
	DoublyLinkedListNode<E> prev;
	
	public DoublyLinkedListNode(E element) {
		this.element = element;
	}
}
