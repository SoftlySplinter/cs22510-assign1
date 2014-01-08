package com.alexanderdbrown.abstract_data_types.linked_lists;

public class SinglyLinkedList<E> implements LinkedList<E> {

	private SinglyLinkedListNode<E> head;

	private int length;

	public SinglyLinkedList() {
		length = 0;
	}

	@Override
	public void insert(E element) {
		insert(element, 0);
	}

	@Override
	public void insert(E element, int position) {
		if (position < 0 || position > length) {
			throw new LinkedListIndexOutOfBoundsException(position);
		}
		if (position == 0) {
			if (length == 0) {
				head = new SinglyLinkedListNode<E>(element);
			} else {
				SinglyLinkedListNode<E> temp = new SinglyLinkedListNode<E>(
						element);
				temp.next = head;
				head = temp;
			}
		} else {
			SinglyLinkedListNode<E> current = head;
			int currentPos = 0;
			while (currentPos != position - 1) {
				current = current.next;
				currentPos++;
			}
			current.next = new SinglyLinkedListNode<E>(element);
		}
		length++;
	}

	@Override
	public void insertToTail(E element) {
		insert(element, length);
	}

	@Override
	public E remove() {
		return remove(0);
	}

	@Override
	public E remove(int position) {
		if (position < 0 || position > length || isEmpty()) {
			throw new LinkedListIndexOutOfBoundsException(position);
		}

		E element = null;
		if (position == 0) {
			element = head.element;
			head = head.next;
		} else {
			SinglyLinkedListNode<E> current = head;
			int currentPos = 0;
			while (position - 1 != currentPos) {
				current = current.next;
				currentPos++;
			}
			SinglyLinkedListNode<E> parent = current;
			current = current.next;
			parent.next = current.next;

			element = current.element;
		}

		length--;
		return element;
	}

	@Override
	public E removeFromTail() {
		return remove(length - 1);
	}

	public E get() {
		return get(0);
	}

	public E get(int index) {
		if (index < 0 || index > length || isEmpty()) {
			throw new LinkedListIndexOutOfBoundsException(index);
		}

		E element = null;
		if (index == 0) {
			element = head.element;
		} else {
			SinglyLinkedListNode<E> current = head;
			int currentPos = 0;
			while (index - 1 != currentPos) {
				current = current.next;
				currentPos++;
			}
			current = current.next;
			element = current.element;
		}
		return element;
	}

	public E getFromTail() {
		return get(length - 1);
	}

	@Override
	public boolean isEmpty() {
		return length == 0;
	}

	@Override
	public int length() {
		return length;
	}
}
