import os


class Memory:
    def __init__(self,SIZE):
        self.mem = [0]*SIZE;    
        self.size = SIZE

    def loadData(self,index : int):
        if index>=self.size or index<self.size:
            raise IndexError()

        return self.mem[index]        
        
    def writeData(self,index,value):
        if index>=self.size or index<self.size:
            raise IndexError()
        
        self.mem[index] =value;


class CPU:
    
    def __init__(self,REG,memory):
        self.registers=[0]*REG
        self.memory =memory
        pass

    def add(self,val1,val2):
        return val1+val2
    
    def sub(self,val1,val2):
        return val1-val2
    
    def _and(self,val1,val2):
        return val1 and val2
    
    def _or(self,val1,val2):
        return val1 or val2
    
    def mul(self,val1,val2):
        return val1 *val2
    
    def loadMemFromReg(self,reg):
        return self.memory.loadData([self.registers[reg]])
    
    def writeMemFromReg(self,reg,val):
        self.memory.writeData(self.registers[reg],val)

    def immToReg(self,src,dest):
        self.registers[dest]=self.memory.loadData(self.registers[dest])

    def memToReg(self,src,dest):
        self.memory.writeData(self.registers[dest],self.registers[src])

    


class Computer:
    def __init__(self,SIZE,REGISTER):
        self.memory = Memory(SIZE)
        self.cpu=CPU(REGISTER,self.memory)
        self.temp = 0

    def saveFromTemp(self,dest):
        self.cpu.registers[dest] = self.temp

    def display(self,reg):
        print(self.cpu.registers[reg])


    def start(self):
        os.system("cls")
        print("Starting Computer!")

        while(True):
            cmd = input(">>>")
            if(cmd[0]=="!"):
                os.system(cmd[1:])
            else:
                l=cmd.split(" ")
                if(l[0]=='ADD'):
                    self.temp=self.cpu.add(int(l[1]),int(l[2]))

                elif(l[0]=='SUB'):
                    self.temp=self.cpu.sub(int(l[1]),int(l[2]))

                elif(l[0]=='AND'):
                    self.temp=self.cpu._and(int(l[1]),int(l[2]))

                elif(l[0]=='OR'):
                    self.temp=self.cpu._or(int(l[1]),int(l[2]))

                elif(l[0]=='MUL'):
                    self.temp=self.cpu.mul(int(l[1]),int(l[2]))

                elif(l[0]=="sft"):
                    self.saveFromTemp(int(l[1]))

                elif (l[0]=="dtemp"):
                    print(self.temp)

                    
                elif(l[0]=='display'):
                    self.display(int(l[1]))



if __name__=="__main__":
    Computer(100,10).start()
    