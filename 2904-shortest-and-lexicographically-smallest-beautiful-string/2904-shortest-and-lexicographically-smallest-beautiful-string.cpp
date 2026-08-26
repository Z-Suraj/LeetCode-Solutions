class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n= s.length();

        string answer="";
        int minlength=n+1;
        //start position
        for(int i=0;i<n;i++){

            int ones=0;

            //end position
            for(int j=i;j<n;j++){

                if(s[j]=='1'){
                    ones++;

                }
                if(ones==k){

                    string sub=s.substr(i,j-i+1);
                    // shorter substring find 
                    if (sub.length()<minlength){

                        minlength=sub.length();
                        answer=sub;

                    }
                    else if(sub.length()==minlength && sub < answer){
                        answer=sub;

                    }
                    break ;

                }
                if(ones>k){
                    break;
                }
            }
        }
        return answer;

    }
};