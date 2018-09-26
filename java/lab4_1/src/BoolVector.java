public class BoolVector {

    public BoolVector() {
        _data = null;
    }


    public BoolVector(int n, boolean val) {
        _data = new boolean[n];
        for(int i = 0; i < _data.length; ++i) {
            _data[i] = val;
        }
    }

    public BoolVector(boolean[] data) {
        _data = new boolean[data.length];
        for(int i = 0; i < _data.length; ++i) {
            _data[i] = data[i];
        }
    }

    public String toString() {
        String str = "[";
        for(int i = 0; i < _data.length; ++i) {
            if(_data[i])
                str += "1";
            else
                str += "0";
        }
        str += "]";
        return str;
    }

    public int countOnes() {
        int ones = 0;
        for(int i = 0; i < _data.length; ++i) {
            if(_data[i]) {
                ones++;
            }
        }

        return ones;
    }

    public int countZeros() {
        return length() - countOnes();
    }

    public int length() {
        return _data.length;
    }

    public boolean getAt(int pos) throws Exception {
        if (pos >= _data.length) {
            throw new Exception("index is out of range");
        }
        return _data[pos];
    }

    public void setAt(int pos, boolean val) throws Exception {
        if (pos >= _data.length) {
            throw new Exception("index is out of range");
        }
        _data[pos] = val;
    }

    public void inverse() {
        for(int i = 0; i < _data.length; ++i) {
            _data[i] = !_data[i];
        }
    }

    public BoolVector inversed() {
        BoolVector newVector = new BoolVector(_data);
        newVector.inverse();
        return newVector;
    }

    public BoolVector conjunction(BoolVector other) throws Exception {
        if(length() != other.length()) {
            throw new Exception("incompatible operands lenghts");
        }

        BoolVector newVector = new BoolVector(length(), false);
        for(int i = 0; i < _data.length; ++i) {
            newVector._data[i] = _data[i] && other._data[i];
        }

        return newVector;
    }

    public BoolVector disjunction(BoolVector other) throws Exception {
        if(length() != other.length()) {
            throw new Exception("incompatible operands lenghts");
        }
        BoolVector newVector = new BoolVector(length(), false);
        for(int i = 0; i < _data.length; ++i) {
            newVector._data[i] = _data[i] || other._data[i];
        }

        return newVector;
    }

    private boolean[] _data;
}
