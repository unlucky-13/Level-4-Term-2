## Report on Assignment-2
### Submitted By : Shamik Roy(1105053) Md Mazharul Islam(1105013)

#### Data:
**Naïve Bayes:**

Mean Accuracy       | Standard Deviation  
------------------- | -----------------
93% (approximately) | 1.7% (approximately)

**K-NN:**

Mean Accuracy       | Standard Deviation  
------------------- | -----------------
82% (approximately) | 3.6% (approximately)

**t-statistics**

* Null Hypothesis: 
  * Mean Accuracy(NB) – Mean Accuracy(KNN) >= 12
* Alternative Hypothesis: 
  * Mean Accuracy(NB) – Mean Accuracy(KNN)  < 12

**Result**
  * t(absolute) = 1.4747 
  * D.O.F = 71
  * At significance level of 0.05: t(critical) = 1.66715
  * So, t(absolute) < t(critical)

**The Null Hypothesis cannot be rejected and the Alternative Hypothesis cannot be accepted.**
 * At significance level of 0.01: t(critical) = 2.3812 
 * So, t(absolute) < t(critical) The Null Hypothesis cannot be rejected and the Alternative Hypothesis cannot be accepted.
 * At significance level of 0.005: t(critical) = 2.64845 So, t(absolute) < t(critical)

**The Null Hypothesis cannot be rejected and the Alternative Hypothesis cannot be accepted.**


So, with higher confidence level we can conclude that the actual mean accuracy of Naïve Bayes algorithm is at least 12% more than the actual mean accuracy of K-NN algorithm. Hence, Naïve Bayes is better than K-NN.
