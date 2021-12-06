data = []
File.foreach('input.txt') do |line|
    line.match(/(\d+),(\d+) -> (\d+),(\d+)/) do|m| 
        data << {:start => m[1..2].map(&:to_i), :end => m[3..4].map(&:to_i)}
    end
end
max_x = (data.map { |n| n[:start][0]} + data.map { |n| n[:end][0]}).max
max_y = (data.map { |n| n[:start][1]} + data.map { |n| n[:end][1]}).max
field = Array.new((max_x + 1) * (max_y + 1), 0)

def inc_point!(s, e)
    diff = true
    if s[0] != e[0]
        s[0] += (s[0] > e[0]) ? -1 : 1    
        diff = false
    end
    if s[1] != e[1]
        s[1] += (s[1] > e[1]) ? -1 : 1
        diff = false
    end
    return diff
end

data.map do |n|
    loop do
        field[n[:start][0] + n[:start][1] * max_x] += 1
        if inc_point!(n[:start], n[:end])
            break
        end
    end
end

puts (field.select { |n| n > 1}).size