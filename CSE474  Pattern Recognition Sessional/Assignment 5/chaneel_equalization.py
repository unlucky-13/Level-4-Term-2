import  random
import  numpy as np

def getBit(ID,pos):                    # will return the bit at the position
    #print  ID ," ",(1<<pos)
    if (ID & (1<<pos))>0: return 1 # 0001  010
    return 0
def is_neighbour(ID1, ID2,l):  # from ID1 to ID2
    for i in range(0, l-1):
        if getBit(ID1, i) != getBit(ID2, i + 1): return False

    return True

class State:

   def __init__(self,ID,l):
       self.ID = ID
       self.l = l ;
       self.TransmitionProbability=[]                  ## Setting up the transmition probability
       self.ObservationProbability = []
       count=0.0

       for  i in range(0,pow(2,l)):
          if is_neighbour(ID,i,l):
             # print  "from ID ->",ID," to ",i
              count+=1.0
       #print  count
       for i in range(0,pow(2,l)):
           if is_neighbour(ID,i,l):
               self.TransmitionProbability.append(1/count)
           else:
               self.TransmitionProbability.append(0.00)
        ##  Observation probabilty is going to be trained
class Channel:
    def  __init__(self,_dependsOn,H,_mean,_variance):
        self.l = _dependsOn
        self.mean = _mean # Noise's mean
        self.variance=_variance # Noise er Vairance
        #Now randomly assign H
        self.H = H

    def simulate(self,sequence):
        out=np.random.normal(self.mean,self.variance)-mean  # Noise is added
        #print len(sequence)
        for i in range(0,len(sequence)):
            out+=sequence[i]*H[i]



        return out

    def transmit(self,sequence):
        outSequence=[]  # what for the initial sequence ??
        for i in range(len(sequence)):
            seq=[]
            for k in range(i-self.l,i):
                    if k>0: seq.append(sequence[k])
            #print  len(seq)
            outSequence.append(self.simulate(seq))
        return outSequence

if __name__=='__main__':

    ################################################### Channel Simulation#############################################################
    f =  open("channel_description.in",'r')
    depends_on = int(f.readline())
    H = map(float,f.readline().split())
    mean = float(f.readline())
    variance = float(f.readline())
    #print H," ",mean," ",variance," ",depends_on
    #print depends_on," ",H," ",variance

    channel = Channel(depends_on,H,mean,variance)
    sequence = [1,-1,1,1,1,1-1,1,1,1,1,-1,1,1,1,-1,1,1,-1]
    #print "Encoded Sequence -> ",channel.transmit(sequence)
    #print channel.simulate([1,1,-1])
    states = []
    for i in range(0,pow(2,channel.l)):
        states.append(State(i,depends_on))
    #for i in range(len(states)):
        #print states[i].ID
    #0111 1110
    #print  is_neighbour(0b000,0b000,2)
    ####################################################Training###########################################################################
    iterations=100
    Len=100
    while iterations>0:
        iterations-=1
        # generate a random sequence
        sequence=[]
        for i in range(Len):
            val = random.randint(0,10000)
            if val%2==0: val=1
            else : val=-1
            sequence.append(val)

        #print  sequence
        outSequence=channel.transmit(sequence)
        #print  outSequence
