
public class Enrollee implements Comparable<Enrollee>
{
	private String userid;
	private String fname;
	private String lname;
	private String insurance;
	private String version;
	
	public Enrollee()
	{
		this.userid = "";
		this.fname = "";
		this.lname = "";
		this.insurance = "";
		this.version = "";
	}

	public String getUserid() {
		return userid;
	}

	public void setUserid(String userid) {
		this.userid = userid;
	}

	public String getFname() {
		return fname;
	}

	public void setFname(String fname) {
		this.fname = fname;
	}

	public String getLname() {
		return lname;
	}

	public void setLname(String lname) {
		this.lname = lname;
	}

	public String getInsurance() {
		return insurance;
	}

	public void setInsurance(String insurance) {
		this.insurance = insurance;
	}

	public String getVersion() {
		return version;
	}

	public void setVersion(String version) {
		this.version = version;
	}

	@Override
	public int compareTo(Enrollee o) {
		int compare = insurance.compareTo(o.insurance);
		
		if (compare == 0)
		{
			compare = lname.compareTo(o.lname);
			
			if (compare == 0)
			{
				compare = fname.compareTo(o.fname);
				
				if (compare == 0)
				{
					compare = userid.compareTo(o.userid);
					
					if (compare == 0)
					{
						compare = version.compareTo(o.version);
					}
				}
			}
		}
		
		return compare;
	}
	
	public String toString()
	{
		return userid + "," + fname + "," + lname + "," + insurance + "," + version + "\n";
	}
}
