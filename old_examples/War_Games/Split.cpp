int Split(string str, char checker, string words[], int array_size){
    string subsent;
    int c = 0;
    int j = 0;
    int count = 0;
    string tester = checker + str + checker;
    if(str.length() != 0){
        for(int i = 0; i < tester.length(); i++){
            if(tester[i] == checker && i != 0){
                subsent = tester.substr((c+1),(i-c-1));
                //cout << subsent << endl;
                //cout << i << endl;
                if(subsent.length() > 0){
                    words[j] = subsent;
                    count++;
                    j++;
                }
                c = i;
            }
        }
        return count;
    }
    else{
        return 0;
    }
}
