public class Branch {

    private int id;
    private String name;
    private Account []  accounts;
    private int accountCount;
	// add your code here
	// there can be at most 20 branches
	static int numberofbranches = 0;
	static Branch[] allbranches = new Branch[30];

     // you are not allowed to write any other constructor
    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        this.accounts = new Account[10];
        // add your code here
		allbranches[numberofbranches] = this;
		numberofbranches++;
	}

    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }

    // add your code here
	double getBranchBalance(){
		double total = 0;
		for (int i = 0; i<accountCount; i++) {
			total += accounts[i].getBalance ();
		}
		return total;
	}
	
	Account getMinBalanceAccount(){
		double mn = Double.MAX_VALUE;
		int mni = 0;
		for (int i = 0; i<accountCount; i++) {
			if (accounts[i].getBalance ()<mn) {
				mn = accounts[i].getBalance ();
				mni = i;
			}
		}
		return accounts[mni];
	}
	
	static void transferBalance(Account from, Account to, double amount){
		if (from.getBalance ()>amount) {
			System.out.println ("Not sufficient ammount");
		}
		else {
			from.setBalance (from.getBalance ()-amount);
			to.setBalance (to.getBalance ()+amount);
		}
	}
	
	static void printAllBranchesInfo(){
		int cnt = 1;
		for (int i = 0; i<numberofbranches; i++) {
			System.out.println ("Branch Id: "+allbranches[i].id+", Branch Name: "+allbranches[i].name);
			for (int j = 0; j<allbranches[i].accountCount; j++) {
				System.out.println ("Account number: "+cnt+", customer name: ACC"+cnt+", Balance: "+allbranches[i].accounts[j].getBalance ());
				cnt++;
			}
		}
	}
}
