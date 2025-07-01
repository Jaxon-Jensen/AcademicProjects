package DataStructures.Assign2;

public class Assign2_3 {      
    class Node{    
        int data;    
        Node next;    
            
        public Node(int data) {    
            this.data = data;    
            this.next = null;    
        }    
    }    
    Node head = null;    
    Node tail = null;    
    public void enqueue(int data) {     
        Node newNode = new Node(data);      
        if(head == null) {     
            head = newNode;    
            tail = newNode;    
        } else {       
            tail.next = newNode;     
            tail = newNode;}    
    }   
    public int dequeue(){
        if(head != null){
            int val = head.data;
            head = head.next;
            System.out.println(val);
            return val;
        } else {
            System.out.println("Queue is empty");
            return -1;}
    }
    public static void main(String[] args) {      
        Assign2_3 list = new Assign2_3();       
        list.enqueue(1);    
        list.enqueue(2);    
        list.enqueue(3);  
        list.dequeue();  
        list.enqueue(4);
        list.dequeue();    
    }    
}    