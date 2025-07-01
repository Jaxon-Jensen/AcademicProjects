package DataStructures.Assign4;

public class Assign4_1 {
    public static void main(String[] args){
        LinkedList list = new LinkedList(1);
        int a = 0;
        for(int i = 0; i< 20; i++){
            a = (int) (Math.random() *20)+1;
            list.add(a);
        }
        list.print();
        list.sort();
        System.out.println();
        list.print();
    }
}
class LinkedList{
    Node head;
    public LinkedList(int value){
        head = new Node(value);
    }
    public void add(int data){
        Node temp = head;
        while(temp.next != null){
            temp = temp.next;
        }
        temp.next = new Node(data);
    }
    public void print(){
        Node temp = head;
        while(temp.next != null){
            System.out.print(temp.data + ", ");
            temp = temp.next;
        }
        System.out.println(temp.data);
    }
    public void sort(){
        if(head.next == null){
            return;
        }
        Node current = head.next;
        LinkedList list = new LinkedList(head.data);
        Node previous = null;
        Node temp = list.head;
        Node next = current.next;
        int count = 0;
        while(current.next != null){
            while(current.data > temp.data){
                if(temp.next == null){
                    previous = temp;
                    temp = null;
                    break;
                } else {
                    previous = temp;
                    temp = temp.next;
                }
            }
            if(previous == null){
                if(temp.next == null){
                    list.add(current.data);
                } else {
                    list.head = current;
                    list.head.next = temp;
                }
            } else {
                previous.next = current;
                current.next = temp;
            }
            current = next;
            next = next.next;
            temp = list.head;
            previous = null;
            count++;
        }
        for(int i = 0; i<count; i++){
            if(current.data > temp.data && temp.next != null){
                previous = temp;
                temp = temp.next;
            } else if(current.data > temp.data && temp.next != null){
                list.add(current.data);  
            } else {
                previous.next = current;
                current.next = temp;
            }
        }
        head = list.head;
    }
}
class Node{
    int data;
    Node next;
    public Node(int value){
        data = value;
        next = null;
    }
}