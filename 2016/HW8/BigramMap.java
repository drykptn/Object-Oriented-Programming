package zeytin;


public class BigramMap<T> extends Bigram<T> {
	private int dataType;
	//private map < pair < T , T >, int > bigramList;
	private int sizeOfFile = 0;
	//private vector<pair<T> >couple;
	
	private String fileName;
	
	public BigramMap(int dataType) {
		super();
		this.setDataType(dataType);
	}

	public BigramMap() {
		// TODO Auto-generated constructor stub
	}


	public int getSizeOfFile() {
		return sizeOfFile;
	}

	public void setSizeOfFile(int sizeOfFile) {
		this.sizeOfFile = sizeOfFile;
	}

	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}


	public int getDataType() {
		return dataType;
	}


	public void setDataType(int dataType) {
		this.dataType = dataType;
	}

}
