class Solution {
public:
    int singleNumber(vector<int>& a) {
     sort (a.begin(),a.end());

     int n = a.size();

     for (int i =0;i<n-1;i+=2){

        if (a[i]!=a[i+1]){
            return a[i];

        }
     }
     return a[n-1];
    }
};