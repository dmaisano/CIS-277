interface User {
  id: number; // auto increment
  type: 'student' | 'instructor';
  name: string;
  pass?: string;
}
