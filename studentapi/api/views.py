from rest_framework.viewsets import ModelViewSet
from .models import StudentRecord
from .serializers import StudentRecordSerializer

class StudentRecordViewSet(ModelViewSet):
    queryset = StudentRecord.objects.all()
    serializer_class = StudentRecordSerializer