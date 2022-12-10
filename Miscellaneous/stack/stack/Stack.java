/*
 * AUTHOR: ASHWIN ABRAHAM
 */

public interface Stack {
    public void push(Object o);

    public Object pop() throws StackEmpty;

    public Object top() throws StackEmpty;

    public int size();
}