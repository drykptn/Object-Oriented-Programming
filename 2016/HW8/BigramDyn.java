package zeytin;

import java.io.*;
import java.util.Scanner;

public class BigramDyn<T> extends Bigram <T> {
	private int dataType;
	private T[] bigramList = null;
    private int sizeOfFile = 0;
    private String fileName;
    private Pair<T>[] couple;
    Pair < T > pr = new Pair<T>(null, null);
 
    	
    public void findSize() throws IOException{
    	int count = 0;
    	Scanner in;
    	in = new Scanner( new File(getFileName()) );
    	
    	while (in.hasNext()) {
			@SuppressWarnings("unused")
			String a = in.next();
			count++;
		}   	
    	count--;
    	setSizeOfFile(count);
    	if( in != null )
    		in.close();
 
    }
   @SuppressWarnings("unchecked")
	public void readFile( String filename) throws IOException{
    	setFileName(filename);
    	findSize();
    	Scanner in;
    	in = new Scanner( new File(getFileName()) );
    	int i = 0;
    	bigramList = (T[]) new Object[getSizeOfFile()+1];
    	Pair<T>[] couple = new Pair[getSizeOfFile()+1];
	    
		while (in.hasNext()){
			bigramList[i] = (T) in.next();
			System.out.println(bigramList[i] );
			i++;
		}
	    
		//  add to pair
		for ( int j = 0; j < getSizeOfFile() ; j++ ){
			pr.setFirst( bigramList[j] );
			pr.setSecond( bigramList[j+1] );
			couple[j] = pr;
			System.out.print(couple[j].getFirst());
		    System.out.print(",");
			System.out.print(couple[j].getSecond());
			System.out.print("\n");	
		} 
		
        if (in != null)
    		in.close();
        
        
    }
	@SuppressWarnings({ "unchecked", "unused" })
	public String toString() {
		
		return "";     
	}
	public int numOfGrams( T p1, T p2 ){
	    int i = 0, count = 0; 
	    
	    while( i != getSizeOfFile() )
	    {
	        if( couple[i].getFirst() == p1 )
	        {
	            if( couple[i].getSecond() == p2 )
	                count++;
	        }
	        i++;
	    }          
	    return count;
	}
	public int numGrams(){
	    return getSizeOfFile();
	}
    
	public BigramDyn() {
		// TODO Auto-generated constructor stub
	}


	public BigramDyn(int dataType) {
		super();
		this.setDataType(dataType);
	}


	public int getSizeOfFile() {
		return sizeOfFile;
	}

	public void setSizeOfFile(int num) {
		this.sizeOfFile = num;
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
