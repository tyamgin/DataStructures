    public class BaseConverter
    {
	    public static string Convert(string number, int from, int to) 
        {
		    return ConvertFrom10(ConvertTo10(number, from), to);
	    }

	    public static BigInteger ConvertTo10(string number, int from) 
        {
            BigInteger res = 0;
		    for (var i = 0; i < number.Length; i++)
    			res = res * from + GetInt(number[i]);
		    return res;
	    }

        public static string ConvertFrom10(BigInteger number, int to)
        {
		    var res = "";
		    for (; number > 0; number /= to)
			    res += GetChar((int)(number % to));
            var arr = res.ToCharArray();
            Array.Reverse(arr);
            return res == "" ? "0" : new string(arr);
        }

	    public static char GetChar(int i) 
        {
		    return (char)(i < 10 ? i + '0' : i - 10 + 'A');
	    }

	    public static int GetInt(char c) 
        {
		    return ('0' <= c && c <= '9') ? c - '0' : c - 'A' + 10;
	    }
    }