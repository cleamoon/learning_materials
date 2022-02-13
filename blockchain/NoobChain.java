import java.util.ArrayList;
import com.google.gson.GsonBuilder;

public class NoobChain {
    public static ArrayList<Block> blockchain = new ArrayList<Block>();
    public static int difficulty = 5;
    
    public static void main(String[] args) {
	blockchain.add(new Block("Hi! I'm the first block", "0"));
	System.out.println("Trying to mine block 1...");
	blockchain.get(0).mineBlock(difficulty);
	
	blockchain.add(new Block("Now I am second", blockchain.get(blockchain.size() - 1).hash));
	System.out.println("Trying to mine block 2...");
	blockchain.get(1).mineBlock(difficulty);

	blockchain.add(new Block("I am third", blockchain.get(blockchain.size() - 1).hash));
	System.out.println("Trying to mine block 3...");
	blockchain.get(2).mineBlock(difficulty);

	System.out.println("\nIs Blockchain Valid? " + isChainValid());

	String blockchainJson = new GsonBuilder().setPrettyPrinting().create().toJson(blockchain);
	System.out.println("\nThe block chain is: ");
	System.out.println(blockchainJson);
    }

    public static Boolean isChainValid() {
	Block currentBlock;
	Block previousBlock;

	for (int i = 1; i < blockchain.size(); i++) {
	    currentBlock = blockchain.get(i);
	    previousBlock  = blockchain.get(i-1);

	    if(!currentBlock.hash.equals(currentBlock.calculateHash())) {
		System.out.println("Current hashes not equal");
		return false;
	    }

	    if (!previousBlock.hash.equals(currentBlock.previousHash)) {
		System.out.println("Previous hashes not equal");
		return false;
	    }
	}
	return true;
    }
}
