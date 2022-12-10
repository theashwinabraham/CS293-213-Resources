/*
 * AUTHOR: ASHWIN ABRAHAM
 */

public class ArrayStack implements Stack {
    private java.util.ArrayList<Object> arr;

    ArrayStack()
    {
        arr = new java.util.ArrayList<Object>();
    }

    public void push(Object o)
    {
        arr.add(o);
    }

    public int size()
    {
        return arr.size();
    }

    public Object pop()
    {
        if(size() == 0) throw new StackEmpty();
        return arr.remove(arr.size()-1);
    }

    public Object top()
    {
        if(size() == 0) throw new StackEmpty();
        return arr.get(arr.size()-1);
    }
}
