AVLTREE<int> tree;
    int arr[] = {5, 10, 15};
    for(int x : arr){
        tree.insert(x); tree.view(MODE::BFS);
        cout<<x<<"\n-------------------\n";
    }