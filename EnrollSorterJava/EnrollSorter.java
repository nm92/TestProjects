import java.io.*;
import java.util.*;

public class EnrollSorter {

	// INPUT: 2 enrollee structs/objects
	// OUTPUT: bool value (true/false)
	// FUNCTION: compare all of the values of 2 enrollee structs/objects
	//	         	if they are NOT the same, return true
	//	            if they are the same, return false
	//	            (kind of backwards, but easier to think about when implementing the function in the code below)
	public static boolean notSameEnrollee(Enrollee e1, Enrollee e2)
	{
		// if they have the same attributes, then they must be the same enrollee, so return false
		if ( (e1.getUserid().equals(e2.getUserid())) && (e1.getFname().equals(e2.getFname())) && (e1.getLname().equals(e2.getLname())) && (e1.getInsurance().equals(e2.getInsurance())) && (e1.getVersion().equals(e2.getVersion())) )
		{
			return false;
		}
		// otherwise if they have different attributes, then they are different enrollees, so return true
		else
		{
			return true;
		}
	}
	
	public static void main(String[] args) {
		
		ArrayList<Enrollee> enrolleeAL = new ArrayList<Enrollee>();
		int numDuplicates = 0;
		BufferedReader br = null;
		String inputFileName = "input.csv";
		
		// try statement for opening the input file
		try
		{
			// open the input file
			br = new BufferedReader(new FileReader(inputFileName));
			
			// print info
			System.out.println("----------------------------------------");
			System.out.println("Before Sorting");
			System.out.println("----------------------------------------");
			
			// read in the next line of the input file
			String line;
			while ((line = br.readLine()) != null)
			{
				// split up the line that was just read in, separated by commas, and store them in an array of strings
				String[] splitString = line.split(",");
				
				// create a new Enrollee object
				Enrollee tempEnrollee = new Enrollee();
				
				// assign the input values that were just read in to the new Enrollee object
				tempEnrollee.setUserid(splitString[0]);
				tempEnrollee.setFname(splitString[1]);
				tempEnrollee.setLname(splitString[2]);
				tempEnrollee.setInsurance(splitString[3]);
				tempEnrollee.setVersion(splitString[4]);
				
				// add the Enrollee object to the array list of Enrollees
				enrolleeAL.add(tempEnrollee);
			}
			
			// print enrollees before sorting
			System.out.println(enrolleeAL);
			
			// now that we have read and stored the enrollees in an array list, we must sort them by insurance, then lname, then fname, then userid, then version
			
			// sort the enrolleeAL based on the above criteria written into the class's compareTo() function
			Collections.sort(enrolleeAL);
			
			// print enrollees after sorting
			System.out.println("----------------------------------------");
			System.out.println("After Sorting");
			System.out.println("----------------------------------------");
			System.out.println(enrolleeAL);
			System.out.println("----------------------------------------\n");
			
			// open an output file for the potential deleted enrollees
			String deleteFileName = "deleted.csv";
			PrintWriter writer = new PrintWriter(deleteFileName, "UTF-8");
			
			// now that we have our sorted array list of enrollees, we must delete enrollees w/ duplicate userid's and insurances (store and write deleted entries to output file)
			
			// loop thru the enrolleeAL and compare each object to every other object to check for duplicate id's w/ the same insurance
			for (int i = 0; i < enrolleeAL.size(); i++)
			{
				for (int j = 0; j < enrolleeAL.size(); j++)
				{
					// if the user id's AND the insurances match AND they are not the same object, then erase the one w/ the lower version
					if ( (enrolleeAL.get(i).getUserid().equals(enrolleeAL.get(j).getUserid())) && (enrolleeAL.get(i).getInsurance().equals(enrolleeAL.get(j).getInsurance())) && (notSameEnrollee(enrolleeAL.get(i), enrolleeAL.get(j))) )
					{
						// if i < j, then delete i
						if ( Integer.parseInt(enrolleeAL.get(i).getVersion()) < Integer.parseInt(enrolleeAL.get(j).getVersion()) )
						{
							// print out which enrollees were received from the input file, but deleted due to a duplicate userid/insurance
							writer.println(enrolleeAL.get(i).getUserid() + "," + enrolleeAL.get(i).getFname() + "," + enrolleeAL.get(i).getLname() + "," + enrolleeAL.get(i).getInsurance() + "," + enrolleeAL.get(i).getVersion());
							
							// delete the enrollee
							enrolleeAL.remove(i);
							
							// increment duplicates counter for info later
							numDuplicates++;
							
						}
						else
						{
							// print out which enrollees were received from the input file, but deleted due to a duplicate userid/insurance
							writer.println(enrolleeAL.get(j).getUserid() + "," + enrolleeAL.get(j).getFname() + "," + enrolleeAL.get(j).getLname() + "," + enrolleeAL.get(j).getInsurance() + "," + enrolleeAL.get(j).getVersion());
							
							// delete the enrollee
							enrolleeAL.remove(j);
							
							// increment duplicates counter for info later
							numDuplicates++;
						}
					}
				}
			}
			
			// close the deleted.csv output file
			writer.close();
			
			// if there were duplicates that were detected, then alert the user w/ further related info
			if (numDuplicates > 0)
			{
				System.out.println(numDuplicates + " enrollee(s) were received from the input file, but deleted due to duplicate userid/insurance.");
				System.out.println("Check deleted.csv for list off deleted enrollee(s).\n");
				System.out.println("----------------------------------------");
			}
			// otherwise just alert the user of no duplicates and delete the output deleted.csv file since it is empty and not needed
			else
			{
				// try statement for deleting the output deleted.csv file
				try
				{
					File file = new File(deleteFileName);
					if(file.delete())
					{
						System.out.println("No duplicates detected/deleted, so deleted.csv was deleted.\n");
						System.out.println("----------------------------------------");
					}
					else
					{
						System.out.println("No duplicates detected/deleted, but there was an ERROR deleting deleted.csv.\n");
						System.out.println("----------------------------------------");
					}
				}
				catch (Exception e)
				{
					e.printStackTrace();
				}
			}
			
			// now that we are sorted and have deleted our duplicates, we just need to write them to their respective output files by insurance
			
			// open output file
			String tempInsurance = enrolleeAL.get(0).getInsurance();
			writer = new PrintWriter((tempInsurance + ".csv"), "UTF-8");
			
			// loop thru enrolleeAL and write each object to its respective insurance output file
			for (int i = 0; i < enrolleeAL.size(); i++)
			{
				// if we come across a new insurance name, then open up a new output file for that new insurance
				if ( !(tempInsurance.equals(enrolleeAL.get(i).getInsurance())) )
				{
					// close the previous output file
					writer.close();
					
					// open a new output file with the new insurance name
					tempInsurance = enrolleeAL.get(i).getInsurance();
					writer = new PrintWriter((tempInsurance + ".csv"), "UTF-8");
				}
				
				// write enrollee object to the file
				writer.println(enrolleeAL.get(i).getUserid() + "," + enrolleeAL.get(i).getFname() + "," + enrolleeAL.get(i).getLname() + "," + enrolleeAL.get(i).getInsurance() + "," + enrolleeAL.get(i).getVersion());
			}
			
			// close the output file
			writer.close();
			
		}
		// if the file was not found
		catch (FileNotFoundException e)
		{
			System.out.println("Unable to open file '" + inputFileName + "'");
		}
		// if there was an i/o error
		catch (IOException e)
		{
			e.printStackTrace();
		}
		// this will always happen once at the end no matter what
		finally
		{
			// close the file
			try {
				br.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

}
