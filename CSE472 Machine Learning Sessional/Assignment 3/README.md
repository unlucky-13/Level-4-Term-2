
##                                        CSE472 Machine Learning Sessional
####                           Report On Assignment ( Image Classification Using ANN ) 

####                                 Mazharul Islam ( 1105013)  Shamik Roy	 (1105053)

**1. Why may the validation help to determine appropriate number of nodes in the hidden layer?**

* Training Data is used repeatedly to estimate the weight vectors( including the biases)	of the Neural Network.Validation is used repeatedly to estimate the performance of the learned Neural network. And also used when to stop training once the optimal weight vectors are learned.
We can not tune the number of nodes in the hidden layer on the test data since then it would be give good accuracy on this particular test data.On other arbitrary chosen test data it might give less accuracy.So we split the Train data into train data and validation data.Validation data is not used in Training phase.It helps us to tune the number of nodes in the hidden layer for maximum accuracy of the learned Neural network.Finally the learned network is applied on the test data once to get the final accuracy.


**2. How have you ensured efficient implementation of backpropagation algorithm?**
* We have used incremental gradient descent in updating the weights in back propagation algorithm. Because
  * It converges quickly with respect to number of iterations
  * Reduces run time of the code
  * The effect of error on incremental is more than on batch gradient descent.However in this data set there are very less errors.  incremental gradient descent is the optimal choice in back propagation.
* We have used 2 hidden layers with optimal learning rate.Since Two Hidden layers can represent an arbitrary decision boundary to arbitrary accuracy with rational activation functions( softmax in this case) and can approximate any smooth mapping to any accuracy in back propagation algorithm.Also it makes training the weight vectors relatively easy.Since using more than 2 layers can cause one layer to learn with different speed than the other one taking much time to converge.
* We have used the least number of nodes in the hidden layers that give maximum accuracy since it gives shorter running time and increasing  number of nodes in the hidden layers unnecessarily can cause over fitting.

**3. Compare ANN with Decision tree.**
* ANN and Decision tree both can handle nonlinear relationship among variables.
* Decision tree is easier to understand , visualize ,easy to program for computer systems  whereas ANN acts as a back box for that delivers the result without any explanation,difficult to create for computer systems.
* Decision tree is good for online data ( like stream) compared to ANN in terms of run time and complexity.
* However ANN is pro efficient to give better classification compared to decision trees.
* Also it is easy in ANN to overcome over fitting by using some regularization settings compared to decision tree.
.
