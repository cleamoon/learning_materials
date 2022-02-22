package noobchain;

public class TransactionInput {
    public String transactionOutputId;  // Reference to TransactionOutputs -> transactionId
    public TransactionOutput UTX0;  // Contains the unspent transaction output

    public TransactionInput(String transactionOutputId) {
        this.transactionOutputId = transactionOutputId;
    }
}