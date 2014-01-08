package com.alexanderdbrown.abstract_data_types.linked_lists;

public class DoublyLinkedList<E> implements LinkedList<E> {
	private DoublyLinkedListNode<E> head;
	private DoublyLinkedListNode<E> tail;
	private int length;

	@Override
	public void insert(E element) {
		insert(element, 0);
	}

	@Override
	public void insert(E element, int index) {
		if (index < 0 || index > length) {
			throw new ArrayIndexOutOfBoundsException();
		}

		if (isEmpty()) {
			DoublyLinkedListNode<E> temp = new DoublyLinkedListNode<E>(element);
			head = temp;
			tail = head;
		} else if (index == 0) {
			DoublyLinkedListNode<E> temp = new DoublyLinkedListNode<E>(element);
			temp.next = head;
			head.prev = temp;
			head = temp;
		} else if (index == length) {
			DoublyLinkedListNode<E> temp = new DoublyLinkedListNode<E>(element);
			temp.prev = tail;
			tail.next = temp;
			tail = temp;
		} else {
			int currentPos;
			DoublyLinkedListNode<E> current;
			if (index < length / 2) {
				current = head;
				currentPos = 0;
				while (currentPos != index) {
					current = current.next;
					currentPos++;
				}
				DoublyLinkedListNode<E> next = current.next;
				DoublyLinkedListNode<E> temp = new DoublyLinkedListNode<E>(
						element);
				current.next = temp;
				next.prev = temp;
				temp.next = next;
				temp.prev = current;
			} else {
				current = tail;
				currentPos = length - 1;
				while (currentPos != index) {
					current = current.prev;
					currentPos--;
				}
				DoublyLinkedListNode<E> prev = current.prev;
				DoublyLinkedListNode<E> temp = new DoublyLinkedListNode<E>(
						element);
				current.prev = temp;
				temp.prev = prev;
				temp.next = current;
				if (prev != null) {
					prev.next = temp;
				}
			}
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
	public E remove(int index) {
		if (index < 0 || index > length || isEmpty()) {
			throw new ArrayIndexOutOfBoundsException();
		}

		E element = null;

		if (length == 1) {
			element = head.element;
		} else if (index == 0) {
			element = head.element;
			head = head.next;
			head.prev = null;
		} else if (index == length) {
			element = tail.element;
			tail = tail.prev;
			tail.next = null;
		} else {
			DoublyLinkedListNode<E> current;
			int currentPos;
			if (index < (length - 1) / 2) {
				current = head;
				currentPos = 0;
				while (currentPos != index) {
					current = current.next;
					currentPos++;
				}
			} else {

				current = tail;
				currentPos = length - 1;
				while (currentPos != index) {
					current = current.prev;
					currentPos--;
				}
			}

			element = current.element;
			
			if(current.next != null) {
				current.next.prev = current.prev;
			}

			if (current.prev != null) {
				current.prev.next = current.next;
			}
		}

		length--;
		return element;
	}

	@Override
	public E removeFromTail() {
		return remove(length - 1);
	}

	@Override
	public E get() {
		return get(0);
	}

	@Override
	public E get(int index) {
		if (index < 0 || index > length || isEmpty()) {
			throw new ArrayIndexOutOfBoundsException();
		}

		E element = null;

		if (length == 1) {
			element = head.element;
		} else if (index == 0) {
			element = head.element;
		} else if (index == length) {
			element = tail.element;
		} else {
			DoublyLinkedListNode<E> current;
			int currentPos;
			if (index < (length - 1) / 2) {
				current = head;
				currentPos = 0;
				while (currentPos != index) {
					current = current.next;
					currentPos++;
				}
			} else {

				current = tail;
				currentPos = length - 1;
				while (currentPos != index) {
					current = current.prev;
					currentPos--;
				}
			}

			element = current.element;
		}
		return element;
	}

	@Override
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
