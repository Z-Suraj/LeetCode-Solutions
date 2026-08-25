class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
    for (int multiple = k; ;multiple+=k){

        bool found = false ;
        for(int x: nums){

            if (x==multiple){

                found = true ;
                break;


            }

        }
        //if not present ,return it 
        if(found==false ){
            return multiple;

        }

    }    
    }
};