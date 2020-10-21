class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> m;
        //统计出单词出现的次数
        for(const auto& wd : words){
            ++m[wd];
        }

        multimap<int, string, greater<int>> m2;//默认从小到大
                                            //修改为从大到小
        //按照string大小遍历,字母序遍历
        for(const auto& p : m){
            m2.insert(make_pair(p.second, p.first));
        }

        int num = 0;
        vector<string> ret;
        for(const auto& p : m2){
            if(num < k){
                ret.push_back(p.second);
                num++;
            }
            else
                break;
        }
        return ret;
    }
};