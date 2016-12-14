**Compare and analyze the ac-curacies obtained by different learners: decision stump alone, boosting with 30 rounds, your ID3 implementation.**

Learner	                      | Accuracy   	
-------------------           |------------------------------
Decision stump learner alone  | 75.9176029963
Boosting with 30 rounds	      | 78.0898876404
ID3 	                        | 80.7218969273

**Analysis:**
* Decision stump leaner gives the least accuracy. Boosting with 30 rounds improves this. Since it collects 30 hypothesis and makes a strong hypothesis. But ID3 gives the best accuracy .Because it is a tree which allows more than 1 depth. For decision stump leaner and booting with 30 rounds it was not allowed.

**Compare and analyze the ac-curacies obtained by boosting with different numbers of rounds: 5, 10, 20, 30.**
K	        | Accuracy(%)
----------| -----------
5	        | 73.0674157303
10	      | 74.8913857678
20	      | 76.5543071161
30	      | 78.0898876404

As the number of weak learner ( K) is increased the accuracy is improved also.
