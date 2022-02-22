package noobchain;

import java.util.Date;
import java.util.ArrayList;


public class Block {
	public String hash;
	public String previousHash;
	public String merkleRoot; // our data will be a simple message
	public ArrayList<Transaction> transactions = new ArrayList<Transaction>();
	private long timeStamp;
	private int nonce;

	// Block Constructor
	public Block(String previousHash) {
		this.previousHash = previousHash;
		this.timeStamp = new Date().getTime();
		this.hash = calculateHash();
	}

	public String calculateHash() {
		String hash = StringUtil.applySha256(
				previousHash +
				Long.toString(timeStamp) +
				Integer.toString(nonce) +
				merkleRoot
				);
		return hash;
	}

	public void mineBlock(int difficulty) {
		merkleRoot = StringUtil.getMerkleRoot(transactions);
		String target = new String(new char[difficulty]).replace('\0', '0'); 
		while (!hash.substring(0, difficulty).equals(target)) {
			nonce++;
			hash = calculateHash();
		}
		System.out.println("Block mined!! " + hash);
	}

	public boolean addTransaction(Transaction transaction) {
		if (transaction == null) return false;
		if (previousHash != "0") {
			if (transaction.processTransaction() != true) {
				System.out.println("Transaction failed to process. Discarded.");
				return false;
			}
		}
		transactions.add(transaction);
		System.out.println("Transaction successfully added to Block");
		return true;
	}
}
