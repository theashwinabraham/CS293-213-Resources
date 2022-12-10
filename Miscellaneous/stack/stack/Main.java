/*
 * AUTHOR: ASHWIN ABRAHAM
 */

public class Main {
    public static void main(String[] Args)
    {
        ArrayStack s = new ArrayStack();
        s.push(1);
        s.push(1.1);
        s.push("Hello");
        s.push("lmao");
        System.out.println(s.top());
        s.pop();
        System.out.println(s.top());
        s.pop();
        s.push("new Lmao");
        System.out.println(s.top());
        s.pop();
        System.out.println(s.top());
        s.pop();
        System.out.println(s.pop());
        try
        {
            System.out.println(s.top());
        }
        catch(StackEmpty p)
        {
            System.out.println("The stack is empty");
        }
        try
        {
            System.out.println(s.pop());
        }
        catch(StackEmpty p)
        {
            System.out.println("The stack is empty");
        }
    }
}
