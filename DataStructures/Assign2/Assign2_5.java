package DataStructures.Assign2;

class Node{
    int data;
    Node left, right;
    Node(int data){
        this.data = data;
        left = null;
        right = null;}}
class Tree{
    Node root;
    void paths(Node node){
        int path[] = new int[1000];
        System.out.print("[");
        pathGen(node, path, 0);
        System.out.println("]");
    }
    void pathGen(Node node, int path[], int pLength){
        if (node == null){
            return;}
        path[pLength] = node.data;
        pLength++;
        if (node.left == null && node.right == null){
            printPath(path, pLength);
        } else {
            pathGen(node.left, path, pLength);
            pathGen(node.right, path, pLength);}
    }
    void printPath(int arr[], int length){
        System.out.print("\"");
        for (int i = 0; i < length-1; i++){
            System.out.print(arr[i] + "->");
        }
        System.out.print(arr[length-1] + "\",");}
    public static void main(String args[])
    {
        Tree tree = new Tree();
        tree.root = new Node(1);
        tree.root.left = new Node(2);
        tree.root.right = new Node(3);
        tree.root.left.right = new Node(5);
        tree.paths(tree.root);}}