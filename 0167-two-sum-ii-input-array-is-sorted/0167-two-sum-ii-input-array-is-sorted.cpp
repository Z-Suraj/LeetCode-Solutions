class Solution {
public:
    vector<int> twoSum(vector<int>& num, int target) {
       int i=0;
       int j=num.size()-1;
       while(i<j){
        int sum = num[i] + num[j];
        if(sum==target){
        return{i+1,j+1};
       }

       else if (sum<target){

        i++;
       }
        else{

        
        j--;
       }
    }
    return{}; 
    }
};